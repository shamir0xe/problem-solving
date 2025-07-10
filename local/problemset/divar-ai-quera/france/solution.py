from typing import List
from urllib.parse import urljoin, urlparse
import requests
from openai import OpenAI
from bs4 import BeautifulSoup
import json
import math


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
                "content": """
    You are a hyper-efficient AI agent built for a programming contest.
    Your primary directive is to follow instructions with absolute precision.
    Analyze the user's prompt, perform all necessary reasoning internally, and provide ONLY the final, requested answer.
    Do NOT include any conversational filler, apologies, explanations, or restatements of the question.
    Your output must be the direct result of the user's instruction, and nothing more.
    Your OUTPUT SHOULD BE IN ONE WORD, DON'T OUTPUT ANYTHING ELSE.
    """,
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
                    function_args = json.loads(tool_call.function.arguments)

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

        return final_result

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
        ]


def sum_list(numbers: List[int | float]):
    """
    Calculates the sum of a list of integers.
    Use this when you need to add multiple numbers together from a list.
    """
    try:
        print(f"--- Calling Tool: sum_list with numbers: {numbers} ---")
        if not isinstance(numbers, list):
            return "Error: Input must be a list of numbers."

        total = sum(numbers)
        return {"sum": total}

    except TypeError:
        return "Error: All items in the list must be numbers (integers)."
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


chunk_size = 4000
URL_CONTENT_CACHE = {}
CHUNK_SIZE_CHARS = 4000


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


# def fetch_url(url: str, chunk: int):
#     """
#     Fetches the content from a given URL and returns the main text content.
#     Use this to get information from a webpage.
#     """
#     try:
#         print(f"--- Calling Tool: fetch_url with url: {url}/{chunk} ---")
#         response = requests.get(url, timeout=10)
#         response.raise_for_status()  # Raises an HTTPError for bad responses (4xx or 5xx)
#
#         # Use BeautifulSoup to parse the HTML and get clean text
#         soup = BeautifulSoup(response.text, "html.parser")
#
#         # Remove script and style elements
#         for script_or_style in soup(["script", "style"]):
#             script_or_style.decompose()
#
#         # Get text and clean it up
#         text = soup.get_text()
#         lines = (line.strip() for line in text.splitlines())
#         chunks = (phrase.strip() for line in lines for phrase in line.split("  "))
#         text = "\n".join(chunk for chunk in chunks if chunk)
#
#         return text[
#             (chunk - 1) * chunk_size : chunk * chunk_size
#         ]  # Return a snippet to avoid huge token counts
#
#     except requests.RequestException as e:
#         return f"Error fetching URL: {e}"
