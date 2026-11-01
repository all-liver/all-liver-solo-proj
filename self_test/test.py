import sys
import os
import subprocess
import time
import glob
import re

# ANSI Color Codes
RED = '\033[0;31m'
GREEN = '\033[0;32m'
NC = '\033[0m'
YELLOW = '\033[1;33m'

def run_test(file_name, task):
    print(f"\n---------------Task {task}---------------")

    # Produce the executable
    compile_cmd = ["g++", "-std=c++14", f"{file_name}.cpp", "-o", file_name]
    subprocess.run(compile_cmd, check=False)

    folder_name = f"Task{task}"
    
    # Find test files
    pattern = os.path.join(folder_name, f"{task}-*.in")
    test_files = glob.glob(pattern)
    
    # Sort files naturally (mimicking bash `sort -V`)
    def extract_number(filepath):
        match = re.search(f"{task}-(.+)\\.in$", filepath)
        if match:
            try:
                return int(match.group(1))
            except ValueError:
                return match.group(1)
        return 0
        
    test_files.sort(key=extract_number)

    total_tests = 0
    passed_tests = 0
    
    for input_file in test_files:
        total_tests += 1
        
        # Extract test number from filename
        base_in = os.path.basename(input_file)
        test_num = re.sub(f"^{task}-|\\.in$", "", base_in)
        
        # Get corresponding output file
        output_file = os.path.join(folder_name, f"{task}-{test_num}.out")

        if not os.path.isfile(output_file):
            print(f"Missing output file for test {test_num}: {output_file}")
            continue
            
        print(f"Test Case {test_num}: {base_in}")

        # Read expected output (stripping mimics bash $() behavior)
        with open(output_file, 'r') as f:
            expected = f.read().strip()
            
        # Read input data
        with open(input_file, 'r') as f:
            input_data = f.read()

        # Execute and measure time
        start_time = time.perf_counter()
        
        try:
            # Run the compiled program, feeding it the input data
            proc = subprocess.run([f"./{file_name}"], input=input_data, capture_output=True, text=True)
            result = proc.stdout.strip()
        except Exception as e:
            result = f"Error: {e}"
            
        end_time = time.perf_counter()
        elapsed = end_time - start_time
        
        # Check if the output is correct and within the 1-second time limit
        if result == expected and elapsed <= 1.0:
            status = f"{GREEN}✓ PASS{NC}"
            passed_tests += 1
        else:
            status = f"{RED}✗ FAIL{NC}"
            
        print(f"Status: {status}")
        print(f"Expected Output: {expected}")
        print(f"Your Output: {result}")
        print(f"Execution Time: {elapsed:.3f} seconds")
        print("----------------------------------------")
        
    # Print summary
    print("\n============ TEST SUMMARY ==============")
    print(f"Total Tests: {total_tests}")
    print(f"Passed: {GREEN}{passed_tests}{NC}")
    print(f"Failed: {RED}{total_tests - passed_tests}{NC}")
    
    if total_tests > 0 and passed_tests == total_tests:
        print(f"{GREEN}All tests passed! 🎉{NC}")
    else:
        print(f"{RED}Some tests failed! ❌{NC}")

    print("\nWARNING: This is a program for self-testing only.")
    print("The results you get here is NOT a 100% guarnetee on your final grade!!!")
    print("You should also use the online compiler stated to check your work!!!")
    print("")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python test.py <file_name.cpp> <task>")
        sys.exit(1)
        
    # Replicating bash substring removal: file_name=$(basename "${1#./}" .cpp)
    raw_arg = sys.argv[1]
    if raw_arg.startswith("./"):
        raw_arg = raw_arg[2:]
        
    file_name = os.path.splitext(os.path.basename(raw_arg))[0]
    print(file_name)
    
    task = sys.argv[2]
    
    run_test(file_name, task)
    
    # Clean up the compiled executable 
    if os.path.exists(file_name):
        os.remove(file_name)