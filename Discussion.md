1. Line-by-Line Scanning (Chosen Approach)
Approach: Read the log file line-by-line and extract matching entries based on the provided date.
Pros:
Efficient for large files (~1TB) since it doesn't load the entire file into memory.
Works well with a sequentially structured log format.
Simple implementation with ifstream and getline().
Cons:
Might take time if the relevant logs are located toward the end of the file.
2. Binary Search (Requires Sorted File)
Approach: Apply binary search on the timestamps to find the start and then scan forward.
Pros
It is faster than a full scan if the file is sorted.
Reduces unnecessary reads of old logs.
Cons
Requires indexed logs or sorted timestamps.
Not feasible without modifying the log file structure.
3. External Tools, for example, grep, awk
Approach: Use Unix tools to filter the logs. For example, use grep "YYYY-MM-DD" logs_2024.log
Pros
Extremely fast if the log format is structured.
Avoid writing custom parsing logic.
Cons
Not cross-platform (does not natively run on Windows).
Requires shell environment, thus is less portable.
Summary of the Final Solution
The approach taken was scanning line-by-line since:
Treats big files without loading into memory.
It is cross-platform compatible. Runs on Windows, Linux, and macOS.
Extra Information
In case the output/ directory is not existing, it automatically gets created.
It runs quite fast for log files of big sizes (~1TB) with low memory usage.
No pre-processing is required as it runs on raw log files.
Simple to implement and does not need complex data structures.
