import java.io.*;
import java.util.*;
import java.math.*;
import java.util.regex.*;

public class Timus implements Runnable
{
    public void solve() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        TreeMap<String, Box> a = new TreeMap<String,Box>();
        for(int i = 0; i < n; i++) {
            String[] s = br.readLine().split("[(),. ]");
            if (s[0].equals("Widget")) {
                a.put(s[1], new Box(s[1], Integer.parseInt(s[2]), Integer.parseInt(s[3])));
            }
            else if (s[0].equals("VBox")) {
                a.put(s[1], new VBox(s[1]));
            }
            else if (s[0].equals("HBox")) {
                a.put(s[1], new HBox(s[1]));
            }
            else if (s[1].equals("pack")) {
                Box child = a.get(s[2]);
                Box father = a.get(s[0]);
                father.a.add(child);
                child.isPack = true;
            }
            else if (s[1].equals("set_border")) {
                Box now = a.get(s[0]);
                now.setBorder(Integer.parseInt(s[2]));
            }
            else if (s[1].equals("set_spacing")) {
                Box now = a.get(s[0]);
                now.setSpacing(Integer.parseInt(s[2]));
            }
        }
        
        for(String name : a.keySet()) {
            Box now = a.get(name);
            now.getSize();
            System.out.println(name + " " + now.width + " " + now.height);
        }
    }
    public void run() {
        try {
            solve();
        }
        catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }
    public static void main(String[] args) throws IOException {
        new Thread(new Timus()).start();
    }
}

class HBox extends Box
{
    int cached;
    public HBox(String name) {
        super(name, 0, 0);
        cached = 0;
    }
    @Override
    public void getSize() {
        if (cached > 0) return ;
        cached = 1;
        for(Box box : a) {
            box.getSize();
            width += box.width;
            height = Math.max(height, box.height);
        }
        if (a.size() > 0) width += 2*border + spacing*(a.size()-1);
        if (a.size() > 0) height += 2*border;
    }
}

class VBox extends Box
{
    int cached;
    public VBox(String name) {
        super(name, 0, 0);
        cached = 0;
    }
    @Override
    public void getSize() {
        if (cached > 0) return ; cached = 1;
        for(Box box : a) {
            box.getSize();
            width = Math.max(width, box.width);
            height += box.height;
        }
        if (a.size() > 0) width += 2*border;
        if (a.size() > 0) height += 2*border + spacing*(a.size()-1);
    }
}

class Box implements Comparable
{
    long width, height;
    String name;
    long border, spacing;
    boolean isPack;
    ArrayList<Box> a;
    
    public Box(String name, int width, int height) {
        this.isPack = false;
        this.width = width;
        this.height = height;
        this.border = this.spacing = 0;
        this.name = new String(name);
        this.a = new ArrayList<Box>();
    }
    
    public int compareTo(Object o) {
        if (o instanceof Box) {
            return name.compareTo(((Box) o).name);
        }
        else throw new IllegalArgumentException("Cannot compare!!!");
    }
    
    public void setBorder(int border) {
        this.border = border;
    }
    public void setSpacing(int spacing) {
        this.spacing = spacing;
    }
    public void getSize() {
    }
}
