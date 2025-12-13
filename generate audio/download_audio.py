import json
import os
import requests
from concurrent.futures import ThreadPoolExecutor, as_completed

def download_file(url, filename, folder):
    """Download a single file to the specified folder."""
    try:
        os.makedirs(folder, exist_ok=True)
        filepath = os.path.join(folder, filename)
        if os.path.exists(filepath):
            print(f"Skipped {filename} (already exists)")
            return

        response = requests.get(url, stream=True)
        response.raise_for_status()

        with open(filepath, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                f.write(chunk)

        print(f"Downloaded {filename}")
    except Exception as e:
        print(f"Error downloading {filename}: {e}")

def main():
    # Load the generated JSON
    with open('generated_audio.json', 'r', encoding='utf-8') as f:
        data = json.load(f)

    selectedQori = data['selectedQori']
    downloads = data['downloads']

    print(f"Downloading audio for {len(selectedQori)} qori(s)")

    # Download files concurrently
    with ThreadPoolExecutor(max_workers=5) as executor:
        futures = [executor.submit(download_file, d['url'], d['filename'], d['folder']) for d in downloads]
        for future in as_completed(futures):
            future.result()

    print("Download complete!")

if __name__ == "__main__":
    main()