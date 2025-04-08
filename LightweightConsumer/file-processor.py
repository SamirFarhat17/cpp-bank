import os
import time
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

while not os.path.exists("/app/records/BANK_READY"):
    print("Waiting for bank service to complete...")
    time.sleep(5)

# Absolute path to the records directory
RECORDS_PATH = "/app/records"

class RecordsHandler(FileSystemEventHandler):
    def on_created(self, event):
        if not event.is_directory and event.src_path.endswith(".SUCCESS"):
            print(f"\nSUCCESS file detected: {event.src_path}")
            self.process_records()

    def process_records(self):
        print("Processing files in /app/records:")
        for root, _, files in os.walk(RECORDS_PATH):
            for file in files:
                if file.endswith(".txt"):
                    file_path = os.path.join(root, file)
                    try:
                        with open(file_path, 'r') as f:
                            content = f.read(100)
                            print(f"• {file}: {content}...")
                    except Exception as e:
                        print(f"Error processing {file}: {str(e)}")

if __name__ == "__main__":
    # Ensure directory exists
    os.makedirs(RECORDS_PATH, exist_ok=True)
    
    print(f"Starting file watcher for {RECORDS_PATH}...")
    event_handler = RecordsHandler()
    observer = Observer()
    observer.schedule(event_handler, path=RECORDS_PATH, recursive=True)
    observer.start()

    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        observer.stop()
    observer.join()