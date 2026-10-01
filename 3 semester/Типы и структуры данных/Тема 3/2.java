import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter writer = new PrintWriter(System.out);

        String[] firstLine = reader.readLine().split(" ");
        int n = Integer.parseInt(firstLine[0]);
        int k = Integer.parseInt(firstLine[1]);

        long[] arr1 = new long[n];
        String[] secondLine = reader.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            arr1[i] = Long.parseLong(secondLine[i]);
        }

        String[] thirdLine = reader.readLine().split(" ");

        for (int i = 0; i < k; i++) {
            long target = Long.parseLong(thirdLine[i]);
            long result = findClosest(arr1, target);
            writer.println(result);
        }

        writer.flush();
    }

    private static long findClosest(long[] arr, long target) {
        int left = 0;
        int right = arr.length - 1;

        // Бинарный поиск позиции
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                return arr[mid];
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        long candidate1 = (right >= 0) ? arr[right] : arr[0];
        long candidate2 = (left < arr.length) ? arr[left] : arr[arr.length - 1];

        long diff1 = Math.abs(candidate1 - target);
        long diff2 = Math.abs(candidate2 - target);

        if (diff1 < diff2) {
            return candidate1;
        } else if (diff2 < diff1) {
            return candidate2;
        } else {
            return Math.min(candidate1, candidate2);
        }
    }
}