
import subprocess
import signal
import time
import sys

def run_ping_test(command, lines_to_capture=20):
    try:
        # Start the ping process
        process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        # Capture output lines
        captured_lines = []
        for _ in range(lines_to_capture):
            line = process.stdout.readline()
            if not line:
                break
            captured_lines.append(line.strip())
        
        # Send CTRL+C (SIGINT)
        process.send_signal(signal.SIGINT)
        
        # Capture the statistics after CTRL+C
        while True:
            line = process.stdout.readline()
            if not line:
                break
            captured_lines.append(line.strip())
        
        return captured_lines
    
    except Exception as e:
        print(f"Error: {e}")
        return []

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 test_ping.py <destination>")
        sys.exit(1)
    
    destination = sys.argv[1]
    
    # Test system ping
    print("\n=== Testing system ping ===")
    system_output = run_ping_test(["ping", destination])
    for line in system_output:
        print(line)
    
    # Wait a bit between tests
    time.sleep(1)
    
    # Test ft_ping
    print("\n=== Testing ft_ping ===")
    ft_output = run_ping_test(["./ft_ping", destination])
    for line in ft_output:
        print(line)
    
    # Optional: Compare outputs
    print("\n=== Summary ===")
    print(f"System ping lines: {len(system_output)}")
    print(f"ft_ping lines: {len(ft_output)}")

if __name__ == "__main__":
    main()