package class09;

public class Code01_PathsToNums {

	public static void pathsToNums(int[] paths) {
		if (paths == null || paths.length == 0) {
			return;
		}
		// citiesPath -> distancesArray
		pathsToDistans(paths);

		// distancesArray -> countsArray
		distansToNums(paths);
	}

	public static void pathsToDistans(int[] paths) {
		int cap = 0;
		for (int i = 0; i != paths.length; i++) {
			if (paths[i] == i) {
				cap = i;
			} else if (paths[i] > -1) {
				int cur = paths[i];
				paths[i] = -1;
				int pre = i;
				while (paths[cur] != cur && paths[cur] >-1) {
					int next = paths[cur];
					paths[cur] = pre;
					pre = cur;
					cur = next;
					// if (paths[cur] > -1) {
					// 	int next = paths[cur];
					// 	paths[cur] = pre;
					// 	pre = cur;
					// 	cur = next;
					// } else {
					// 	break;
					// }
				}
				int value = paths[cur] == cur ? 0 : paths[cur];
				while (paths[pre] != -1) {
					int lastPreI = paths[pre];
					paths[pre] = --value;
					cur = pre;
					pre = lastPreI;
				}
				paths[pre] = --value;
			}
		}
		paths[cap] = 0;
	}

	public static void distansToNums(int[] disArr) {
		for (int i = 0; i != disArr.length; i++) {
			int index = disArr[i]; // index 负数 , 首都的index是0
			if (index < 0) {
				disArr[i] = 0; // important
				while (true) {
					index = -index;
					if (disArr[index] > -1) {
						disArr[index]++;
						break;
					} else { // 含义没变过来，还需要继续跳
						int nextIndex = disArr[index];
						disArr[index] = 1;
						index = nextIndex;
					}
				}
			}
		}
		disArr[0] = 1;
	}

	public static void printArray(int[] arr) {
		if (arr == null || arr.length == 0) {
			return;
		}
		for (int i = 0; i != arr.length; i++) {
			System.out.print(arr[i] + " ");
		}
		System.out.println();
	}

	public static void main(String[] args) {
		int[] paths = { 9, 1, 4, 9, 0, 4, 8, 9, 0, 1 };
		printArray(paths);
		pathsToDistans(paths);
		printArray(paths);
		distansToNums(paths);
		printArray(paths);
	}

}
