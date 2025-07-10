import types
import sys
from typing import List
import io
import zipfile
from urllib.parse import urljoin, urlparse
import os
import requests
from openai import OpenAI
from bs4 import BeautifulSoup
import json
import math
import contextlib


VIRTUAL_WORKSPACE = {}
system_prompts = {
    "problem_sovler": """
    You are a hyper-efficient AI agent built for a programming contest.
    Your primary directive is to follow instructions with absolute precision.
    Analyze the user's prompt, perform all necessary reasoning internally, and provide ONLY the final, requested answer.
    Do NOT include any conversational filler, apologies, explanations, or restatements of the question.
    Your output must be the direct result of the user's instruction, and nothing more.
    Your OUTPUT SHOULD BE IN ONE WORD, DON'T OUTPUT ANYTHING ELSE.
    """,
    "cursor": """
You are an automated, robotic software developer. Your sole purpose is to solve programming tasks by calling tools.
You MUST follow this sequence and you are forbidden from talking to the user.

1.  **Download**: Use tools like `process_zip_from_url` to get the filenames.
1.5 **Analyze**: Prior to the filenames you got, get content of each file with `get_file` and analyze each file inorder to see the potential bug.
2.  **Fix**: The moment you identify a bug, your immediate and ONLY next action is to call the `edit_file` tool.
    -   NEVER explain the bug to the user.
    -   ALWAYS generate the complete, corrected file content and pass it to `edit_file`.
3.  **Execute**: After a successful edit, your next action is to call `execute_python_project`.
4.  **Answer**: Once execution is complete, provide ONLY the `stdout` from the execution as the final answer. Do not say anything else.

Your responses must be tool calls, or the final answer. Nothing else.
    """,
}


class DivarContest:
    def __init__(self, api_token):
        self.api_token = api_token
        self.model = "gpt-4.1-mini"
        self.client = OpenAI(
            api_key=self.api_token, base_url="https://api.metisai.ir/openai/v1"
        )

    def capture_the_flag(self, question):
        tools = self._define_tools()
        messages = [
            {
                "role": "system",
                "content": system_prompts["problem_sovler"],
            },
            {
                "role": "user",
                "content": "gnorw si gnihtemos ,txet siht fo esrever eht etirW",
            },  # "Write the reverse of this text, something is wrong"
            {
                "role": "assistant",
                "content": "something is wrong",
            },
            {
                "role": "user",
                "content": "Respond with the word 'SUCCESS' but spell it backwards.",
            },
            {"role": "assistant", "content": "SSECCUS"},
            {"role": "user", "content": question},
        ]
        # A mapping from the function name (str) to the actual Python function object
        available_functions = {
            "fetch_url": fetch_url,
            "sum_list": sum_list,
            "fetch_and_find_links": fetch_and_find_links,
            "process_zip_from_url": process_zip_from_url,
            "execute_python_project": execute_python_project,
            "edit_file": edit_file,
            "get_file": get_file,
        }
        loop = True
        final_result = ""
        while loop:
            loop = False
            response = self.client.chat.completions.create(
                model=self.model,
                messages=messages,
                tools=tools,
                tool_choice="auto",
                max_tokens=100,
                temperature=0.1,
            )
            response_message = response.choices[0].message

            # Step 2: Check if the model wants to call a tool
            tool_calls = response_message.tool_calls
            if tool_calls:
                loop = True
                print(
                    f"--- LLM wants to call a tool: {response_message.tool_calls[0].function.name} ---"
                )
                # Append the assistant's message with tool calls to the message history
                messages.append(response_message)

                # Step 3: Call the tools
                for tool_call in tool_calls:
                    function_name = tool_call.function.name
                    function_to_call = available_functions[function_name]
                    function_args = {}
                    try:
                        function_args = json.loads(tool_call.function.arguments)
                    except:
                        pass

                    # Call the function with the provided arguments
                    function_response = function_to_call(**function_args)

                    # Append the tool's output to the message history
                    messages.append(
                        {
                            "tool_call_id": tool_call.id,
                            "role": "tool",
                            "name": function_name,
                            "content": str(
                                function_response
                            ),  # Ensure content is a string
                        }
                    )

            else:
                final_result = response_message.content.strip()

        return f"\"{final_result}\""

    def _define_tools(self):
        return [
            {
                "type": "function",
                "function": {
                    "name": "fetch_and_find_links",
                    "description": "Fetches the hyperlinks inside a webpage. Use this to find other pages to navigate to.",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "url": {
                                "type": "string",
                                "description": "The full URL of the webpage to scrape.",
                            },
                        },
                        "required": ["url"],
                    },
                },
            },
            {
                "type": "function",
                "function": {
                    "name": "fetch_url",
                    "description": "Fetches a specific chunk of text from a URL, allowing for reading large pages sequentially. The function returns the content of the chunk, the current chunk number, and the total number of chunks available.",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "url": {
                                "type": "string",
                                "description": "The full URL of the webpage to read.",
                            },
                            "chunk_number": {
                                "type": "integer",
                                "description": "The sequential number of the chunk to retrieve, starting with 1. If not provided, it defaults to 1.",
                            },
                        },
                        "required": ["url"],
                    },
                },
            },
            {
                "type": "function",
                "function": {
                    "name": "sum_list",
                    "description": "Calculates the sum of a list of integers.",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "numbers": {
                                "type": "array",
                                "description": "A list of numbers to be added together, e.g., [5, 12.3, 3]",
                                "items": {"type": "number"},
                            },
                        },
                        "required": ["numbers"],
                    },
                },
            },
            {
                "type": "function",
                "function": {
                    "name": "process_zip_from_url",
                    "description": "Downloads a zip file from a URL, extracts its contents in memory, and returns a dictionary where keys are filenames and values are the text content of those files. Use this tool when the user provides a link to a '.zip' file that needs to be inspected.",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "url": {
                                "type": "string",
                                "description": "The direct, full URL to the .zip file.",
                            }
                        },
                        "required": ["url"],
                    },
                },
            },
            {
                "type": "function",
                "function": {
                    "name": "edit_file",
                    "description": "Overwrites a file in the virtual workspace with new, complete content. Use this to apply bug fixes to code.",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "filename": {
                                "type": "string",
                                "description": "The name of the file in the workspace to edit, e.g., 'main.py'.",
                            },
                            "new_content": {
                                "type": "string",
                                "description": "The full, corrected content to write to the file.",
                            },
                        },
                        "required": ["filename", "new_content"],
                    },
                },
            },
            {
                "type": "function",
                "function": {
                    "name": "execute_python_project",
                    "description": "Executes a multi-file Python project from the virtual workspace, correctly handling imports between files. Provide the name of the main script to run.",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "main_filename": {
                                "type": "string",
                                "description": "The filename of the main Python script to run, e.g., 'main.py'.",
                            }
                        },
                        "required": ["main_filename"],
                    },
                },
            },
            {
                "type": "function",
                "function": {
                    "name": "get_file",
                    "description": "Get a content of a file with the `filename` as its name",
                    "parameters": {
                        "type": "object",
                        "properties": {
                            "filename": {
                                "type": "string",
                                "description": "The name of the file",
                            }
                        },
                        "required": ["filename"],
                    },
                },
            },
        ]


def sum_list(numbers: List[int | float]):
    """
    Calculates the sum of a list of numbers.
    Use this when you need to add multiple numbers together from a list.
    """
    try:
        print(f"--- Calling Tool: sum_list with numbers: {numbers} ---")
        if not isinstance(numbers, list):
            return "Error: Input must be a list of numbers."

        total = sum(numbers)
        return {"sum": total}

    except Exception as e:
        return f"An unexpected error occurred: {e}"


def fetch_and_find_links(url: str):
    """
    Lists all found hyperlinks in a url.
    Use this to find potential pages to visit next.
    """
    try:
        print(f"--- Calling Tool: fetch_and_find_links with url: {url} ---")
        response = requests.get(url, timeout=10)
        response.raise_for_status()

        soup = BeautifulSoup(response.text, "html.parser")

        # --- Find all links ---
        links = []
        for a_tag in soup.find_all("a", href=True):
            # Convert relative URL to absolute URL
            absolute_link = urljoin(url, a_tag["href"])
            # Basic filtering to get valid, full URLs
            if urlparse(absolute_link).scheme in ["http", "https"]:
                links.append(absolute_link)

        # Return a structured dictionary
        return {"found_links": list(set(links))}  # Use set to remove duplicate links

    except requests.RequestException as e:
        return f"Error fetching URL: {e}"


URL_CONTENT_CACHE = {}
CHUNK_SIZE_CHARS = 400000


def fetch_url(url: str, chunk_number: int = 1):
    """
    Fetches a specific chunk of text content from a URL. Use this to read large webpages piece by piece.
    Always start with chunk_number 1 and increment to read subsequent parts of the page.
    """
    print(
        f"--- Calling Tool: get_webpage_chunk with url: {url}, chunk: {chunk_number} ---"
    )

    # Check cache first
    if url not in URL_CONTENT_CACHE:
        try:
            # Use the core logic from our previous fetch function
            headers = {"User-Agent": "MyContestAgent/1.0"}
            response = requests.get(url, headers=headers, timeout=10)
            response.raise_for_status()
            soup = BeautifulSoup(response.text, "html.parser")
            for script_or_style in soup(["script", "style"]):
                script_or_style.decompose()
            text = soup.get_text()
            lines = (line.strip() for line in text.splitlines())
            chunks = (phrase.strip() for line in lines for phrase in line.split("  "))
            clean_text = "\n".join(chunk for chunk in chunks if chunk)

            # Store the full, clean text in the cache
            URL_CONTENT_CACHE[url] = clean_text
        except Exception as e:
            return f"Error fetching or parsing URL: {e}"

    full_content = URL_CONTENT_CACHE[url]

    # Calculate total chunks
    total_chunks = math.ceil(len(full_content) / CHUNK_SIZE_CHARS)

    if chunk_number > total_chunks or chunk_number < 1:
        return f"Error: Invalid chunk number. Please request a chunk between 1 and {total_chunks}."

    # Calculate the start and end index for the requested chunk
    start_index = (chunk_number - 1) * CHUNK_SIZE_CHARS
    end_index = start_index + CHUNK_SIZE_CHARS
    content_chunk = full_content[start_index:end_index]

    # Return a structured, informative response
    return {
        "url": url,
        "content_snippet": content_chunk,
        "current_chunk": chunk_number,
        "total_chunks": total_chunks,
        "status": f"Successfully retrieved chunk {chunk_number} of {total_chunks}.",
    }


def process_zip_from_url(url: str):
    """
    Downloads a zip file from a URL, extracts its contents entirely in memory,
    and returns a dictionary of filenames.
    Use this tool specifically when a URL points to a .zip file.
    """
    print(f"--- Calling Tool: process_zip_from_url with url: {url} ---")

    # Basic validation to fail fast if it's obviously not a zip URL
    if not url.lower().endswith(".zip"):
        return "Error: The provided URL does not appear to be a link to a .zip file."

    try:
        # 1. Download the file content in memory
        headers = {"User-Agent": "MyContestAgent/1.0"}
        response = requests.get(url, headers=headers, timeout=20)
        response.raise_for_status()  # Will raise an error for 4xx/5xx responses

        # 2. Treat the binary content as an in-memory file
        in_memory_zip = io.BytesIO(response.content)

        global VIRTUAL_WORKSPACE
        VIRTUAL_WORKSPACE = {}

        # 3. Open and extract the zip file from memory
        with zipfile.ZipFile(in_memory_zip, "r") as zip_ref:
            file_list = zip_ref.namelist()

            for filename in file_list:
                # Ignore MacOS-specific metadata folders/files
                if (
                    filename.startswith("__MACOSX/")
                    or filename.endswith(".DS_Store")
                    or "__pycache__" in filename
                    or filename.endswith("/")
                ):
                    continue
                alter = filename
                idx = alter.rfind("/")
                if idx > 0:
                    alter = alter[idx + 1 :]

                # Read the content of each file in the zip
                with zip_ref.open(filename) as file_in_zip:
                    try:
                        # Attempt to decode as text
                        content = file_in_zip.read().decode("utf-8")
                        # Snippet the content to avoid being too large
                        VIRTUAL_WORKSPACE[alter] = content
                    except UnicodeDecodeError:
                        # If it's not text (e.g., an image), just note that
                        VIRTUAL_WORKSPACE[alter] = (
                            "[Binary Content - Not Readable as Text]"
                        )

        print(f"~~~ {VIRTUAL_WORKSPACE.keys()}")
        if not VIRTUAL_WORKSPACE:
            return "Successfully downloaded and opened the zip file, but it was empty or only contained metadata."

        return VIRTUAL_WORKSPACE.keys()

    except requests.RequestException as e:
        return f"Network error downloading zip file: {e}"
    except zipfile.BadZipFile:
        return "Error: The downloaded file is not a valid zip file or is corrupted."
    except Exception as e:
        return f"An unexpected error occurred: {e}"


def edit_file(filename: str, new_content: str):
    """
    Overwrites a file in the virtual workspace with new content.
    Use this to apply bug fixes to the code before running it.
    The 'new_content' should be the complete, corrected code for the file.
    """
    print(f"--- Calling Tool: edit_file on file: {filename}/\n{new_content} ---")
    if filename not in VIRTUAL_WORKSPACE:
        return f"Error: File '{filename}' not found in the workspace. You must first extract files from a zip."

    VIRTUAL_WORKSPACE[filename] = new_content
    return f"Successfully updated '{filename}' in the virtual workspace."


def get_file(filename: str):
    """
    Get a content of each file
    """
    print(f"--- Calling tool: Get File")
    return VIRTUAL_WORKSPACE[filename]


def execute_python_project(main_filename: str):
    """
    Executes a multi-file Python project from the virtual workspace using a robust
    `exec` model that correctly handles nested files and imports.
    """
    print(f"--- Calling Tool: execute_python_project on main file: {main_filename} ---")

    if main_filename not in VIRTUAL_WORKSPACE:
        return {
            "stdout": "",
            "stderr": f"Error: Main file '{main_filename}' not found in the workspace.",
        }

    # A list to keep track of modules we've manually added to sys.modules
    # so we can clean up afterwards.
    loaded_module_names = []

    try:
        # --- Step 1: Pre-load all dependency files as modules into sys.modules ---
        for filename, code in VIRTUAL_WORKSPACE.items():
            if filename.endswith(".py"):
                # Convert filepath to a valid Python module path
                # e.g., 'public-code-bug-fix/error.py' -> 'public-code-bug-fix.error'
                module_name = os.path.splitext(filename.replace("/", "."))[0]

                # Create a new module object
                module = types.ModuleType(module_name)

                # Execute the code in the context of the new module
                exec(code, module.__dict__)

                # Add the populated module to Python's main module cache
                sys.modules[module_name] = module
                loaded_module_names.append(module_name)
                print(
                    f"--- Pre-loaded module: '{module_name}' from file '{filename}' ---"
                )

        # --- Step 2: Execute the main script ---
        main_code = VIRTUAL_WORKSPACE[main_filename]

        # The globals for the main script can be simple, as all imports
        # will now be resolved correctly via our populated sys.modules.
        main_globals = {"__name__": "__main__"}

        stdout_capture = io.StringIO()
        stderr_capture = io.StringIO()

        with contextlib.redirect_stdout(stdout_capture), contextlib.redirect_stderr(
            stderr_capture
        ):
            exec(main_code, main_globals)

        return {
            "stdout": stdout_capture.getvalue(),
            "stderr": stderr_capture.getvalue() or "No errors.",
        }
    except Exception as e:
        import traceback

        return {
            "stdout": "",
            "stderr": f"Execution failed with an exception:\n{traceback.format_exc()}",
        }
    finally:
        # --- Step 3: Clean up sys.modules to prevent side-effects ---
        for module_name in loaded_module_names:
            if module_name in sys.modules:
                del sys.modules[module_name]
        print("--- Cleaned up loaded modules from sys.modules ---")
