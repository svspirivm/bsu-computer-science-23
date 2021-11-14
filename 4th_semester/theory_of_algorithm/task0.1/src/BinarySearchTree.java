import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.function.Consumer;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

//task
//По набору ключей постройте бинарное поисковое дерево и выполните его прямой левый обход.


public class BinarySearchTree<T extends Comparable<T>> implements Runnable {
    private Node root; // = null

    private class Node {
        T value = null;
        Node left = null;
        Node right = null;
        public boolean isLeaf() {
            return left == null && right == null;
        }
    }

    public BinarySearchTree() {}

    public BinarySearchTree(T[] array) {
        for (T element : array) {
            addElement(element);
        }
    }

    public void addElement(T element) {
        if (root == null) {
            root = new Node();
            root.value = element;
            return;
        }
        Node node = root;
        while (true) {
            if (node.value.compareTo(element) > 0) {
                if (node.left == null) {
                    node.left = new Node();
                    node.left.value = element;
                    //node.left.parent = node;
                    return;
                }
                node = node.left;
            }
            else if (node.value.compareTo(element) < 0) {
                if (node.right == null) {
                    node.right = new Node();
                    node.right.value = element;
                    // node.right.parent = node;
                    return;
                }
                node = node.right;
            }
            else break;
        }
        //throw new IllegalArgumentException("Binary tree already contains " + element);
    }

    public boolean contains(T element) {
        Node node = root;
        while (true) {
            if (node == null) return false;
            if (node.value.compareTo(element) > 0) {
                node = node.left;
            }
            else if (node.value.compareTo(element) < 0) {
                node = node.right;
            }
            else return true;
        }
    }

    public void infixTraverse(Consumer<T> func) { //внутренний левый обход
        if (root == null) return;
        getLeftSubtree().infixTraverse(func);
        func.accept(root.value);
        getRightSubtree().infixTraverse(func);
    }

    public void prefixTraverse(Consumer<T> func) { //прямой левый обход
        if (root == null) return;
        func.accept(root.value);
        getLeftSubtree().prefixTraverse(func);
        getRightSubtree().prefixTraverse(func);
    }

    public void postfixTraverse(Consumer<T> func) { //обратный левый обход
        if (root == null) return;
        getLeftSubtree().postfixTraverse(func);
        getRightSubtree().postfixTraverse(func);
        func.accept(root.value);
    }

    public BinarySearchTree<T> getLeftSubtree() {
        if (root == null) throw new IllegalStateException("Binary tree is empty");
        BinarySearchTree<T> result = new BinarySearchTree<>();
        result.root = root.left;
        return result;
    }

    public BinarySearchTree<T> getRightSubtree() {
        if (root == null) throw new IllegalStateException("Binary tree is empty");
        BinarySearchTree<T> result = new BinarySearchTree<>();
        result.root = root.right;
        return result;
    }

    public static Integer[] ReadFromFile(String path) throws IOException {
        Path filepath = Paths.get(path);
        Scanner scanner = new Scanner(filepath);
        ArrayList<Integer> keys = new ArrayList<Integer>();
        while(scanner.hasNext()) {
            keys.add(scanner.nextInt());
        }
        Integer[] result = keys.toArray(new Integer[0]);
        scanner.close();
        return result;
    }

    public static void main(String[] args) {
        new Thread(null, new BinarySearchTree<Integer>(), "", 64 * 1024 * 1024).start();
    }

    @Override
    public void run() {
        try {
            Integer[] keys = ReadFromFile("./resources/input.txt");
            //keys = ReadFromFile("input.txt");
            BinarySearchTree<Integer> tree = new BinarySearchTree<>(keys);

            File file = new File("./resources/output.txt");
            //File file = new File("output.txt");
            file.createNewFile();

            FileWriter writer = null;
            writer = new FileWriter(file);
            FileWriter finalWriter = writer;
            Consumer<Integer> print = x -> {
                try {
                    finalWriter.write(x + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            };

            tree.prefixTraverse(print);
            writer.close();
        }
            catch (IOException e) {
            e.printStackTrace();
        }
    }
}
