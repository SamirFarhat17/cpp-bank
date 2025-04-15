import os
import time

while not os.path.exists("/app/records/FLAG.SUCCESS"):
    print("Waiting for bank service to complete...")
    time.sleep(5)

# Absolute path to the records directory
RECORDS_PATH = "/app/records"


if __name__ == "__main__":
    # Ensure directory exists
    os.makedirs(RECORDS_PATH, exist_ok=True)
    
    print(f"Starting file processor for {RECORDS_PATH}...")
    time.sleep(5)
    print("Processing files in /app/records:")
    for root, _, files in os.walk(RECORDS_PATH):
        print(f"Visiting: {root}")
        for file in files:
            if file.endswith(".txt"):
                file_path = os.path.join(root, file)
                try:
                    with open(file_path, 'r') as f:
                        content = f.read(100)
                        print(f"• {file}: {content}...")
                except Exception as e:
                    print(f"Error processing {file}: {str(e)}")
