# filepath: c:\Users\samir\Desktop\cpp-bank\LightweightConsumer\Dockerfile
FROM python:3.9-alpine

# Install system dependencies
RUN apk add --no-cache gcc musl-dev python3-dev

# Set the working directory
WORKDIR /app

# Copy the application files
COPY . .

# Install Python dependencies
RUN pip install --no-cache-dir watchdog

# Command to run the application
CMD ["python", "file-processor.py"]