class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        sum = 0.0;
        vals.clear();
        sz = size;
    }
    
    double next(int val) {
        vals.push_back(val);
        sum += val;
        
        if (vals.size() > sz) {
            sum -= vals.front();
            vals.pop_front();
        }
        
        return sum / vals.size();
    }

private:
    deque<double> vals;
    double sum;
    int sz;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
