package com;

class techolution {
    public native boolean assignment(int n);

    // --- Main method to test our native library
    public static void main(String[] args) {
        System.loadLibrary("com_techolution_jni");
        techolution t = new techolution();

	int[] cand = {5, 7, 9, 12};
	for (int i = 0; i < cand.length; ++i)
	{
            System.out.println("Number " + cand[i] + " is " +
                (t.assignment(cand[i]) ? "a " : "not a ") + "prime.");
	}
    }
}
