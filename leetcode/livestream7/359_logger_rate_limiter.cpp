class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        last.clear();
    }
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        if (last.count(message)) {
            if (timestamp - last[message] < 10) {
                return false;
            }
        }
        
        last[message] = timestamp;
        return true;
    }

private:
    map<string, int> last;
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
