/**
 * Created by prd on 28/2/14.
 */

/*
	author: Praveen Dhinwa
	Expected to get TLE.
*/

import java.io.FileNotFoundException;
import java.util.Scanner;


public class Main {

    private static final long INF = (long) 1e9;
    private static final long mod = (long) 1e9 + 7;
    private static long[][][][] memo;
    private static int n;
    private static char s[];
    private static int requiredA;

    public static void main (String[] args) throws FileNotFoundException {
        Scanner sc = new Scanner (System.in);
        int testCase = sc.nextInt();
        while (testCase -- > 0) {
            String str = sc.next();
            requiredA = sc.nextInt();

            n = str.length();
            /*
            memo = new long[n + 2][n + 1][4][2];

            for (int i = 0; i < n + 2; i++) {
                for (int j = 0; j < n + 1; j++) {
                    for (int k = 0; k < 4; k++) {
                        for (int l = 0; l < 2; l++) {
                            memo[i][j][k][l] = -1;
                        }
                    }
                }
            }
		*/
		
            s = new char[n + 1];
            for (int i = 1; i <= n; i++) {
                s[i] = str.charAt (i - 1);
            }

            /*
            for (int i = 1; i <= n; i++)
                System.out.printf ("%c", s[i]);
            System.out.println ();

            /*
            long ans1 = bruteForce();
            System.out.println (ans1);
            */

            long ans2 = doItCorrectly(str, requiredA);
            System.out.println (ans2);

            //if (ans1 != ans2)
            //    throw new RuntimeException();
        }
    }

    private static long doIt(String str, int required) {
        int n = str.length();
        long dp[][][][] = new long[n + 2][n + 3][4][2];

        for (int cntA = required; cntA <= n; cntA++) {
            dp[n + 1][cntA][3][0] = 1;
        }
        //dp[1][0][0][0] = 1;

        for (int i = n; i >= 1; i--) {
            // dp[i][0][0][0] = 1;
            for (int cntA = n; cntA >= 0; cntA --) {
                for (int seg = 3; seg >= 0; seg --) {
                    for (int isRunning = 0; isRunning < 2; isRunning ++) {
                        long res = 0;
                        //System.out.println (" i " + " cnt" + " seg " + "isRunning " + i + " " + cntA + " " + seg + " " + isRunning);
                        if (isRunning > 0) {
                            if (s[i] == 'A') {
                                //System.out.println ("DDD");
                                // end the segment
                                res += dp[i + 1][cntA + 1][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA + 1, cntSegements, 0);

                                // continue;
                                res += dp[i + 1][cntA + 1][seg][1];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA + 1, cntSegements, 1);
                            } else {
                                // end the segment
                                res += dp[i + 1][cntA][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 0);

                                // continue;
                                res += dp[i + 1][cntA][seg][1];
                                res %= mod;
                                // += dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 1);
                            }
                        } else {
                           // System.out.println ("DDDFFF");
                            // make a segment of just size equal to 1.
                            if (s[i] == 'A') {
                                if (seg + 1 <= 3) {
                                   // System.out.println ("LIFE");

                                    // begin and end the segment
                                    res += dp[i + 1][cntA + 1][seg + 1][0];
                                    res %= mod;
                                    //+= dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA + 1, cntSegements + 1, 0);
                                }
                            } else {
                                if (seg + 1 <= 3) {
                                    // begin and end the segment
                                    res += dp[i + 1][cntA][seg + 1][0];
                                    res %= mod;
                                    //+= dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA, cntSegements + 1, 0);
                                }
                            }

                            // do the remaining thing.
                            if (s[i] == 'A') {
                                if (seg + 1 <= 3) {
                                   // System.out.println ("WIFE");

                                    // begin the segment
                                    res += dp[i + 1][cntA + 1][seg + 1][1];
                                    res %= mod;
                                    // += dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA + 1, cntSegements + 1, 1);
                                }
                               // System.out.println ("BANANA");

                                // continue;
                                res += dp[i + 1][cntA][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 0);
                            } else {
                                if (seg + 1 <= 3) {
                                    // begin the segment
                                    res += dp[i + 1][cntA][seg + 1][1];
                                    res %= mod;
                                    //+= dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA, cntSegements + 1, 1);
                                }
                                // continue;
                                res += dp[i + 1][cntA][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 0);
                            }
                        }

                        //System.out.println ("Res " + res);
                        dp[i][cntA][seg][isRunning] = res;
                    }
                }
            }
        }

        long ans = dp[1][0][0][0];

        return ans;
    }

    private static long doItCorrectly(String str, int required) {
        int n = str.length();
        long dp[][][][] = new long[2][n + 3][4][2];

        for (int cntA = required; cntA <= n; cntA++) {
            dp[(n + 1) & 1][cntA][3][0] = 1;
        }
        //dp[1][0][0][0] = 1;

        for (int i = n; i >= 1; i--) {
            // dp[i][0][0][0] = 1;

            for (int cntA = n; cntA >= 0; cntA --) {
                for (int seg = 3; seg >= 0; seg --) {
                    for (int isRunning = 0; isRunning < 2; isRunning ++) {
                        dp[(i & 1)][cntA][seg][isRunning] = 0;
                    }
                }
            }

            for (int cntA = n; cntA >= 0; cntA --) {
                for (int seg = 3; seg >= 0; seg --) {
                    for (int isRunning = 0; isRunning < 2; isRunning ++) {
                        long res = 0;
                        //System.out.println (" i " + " cnt" + " seg " + "isRunning " + i + " " + cntA + " " + seg + " " + isRunning);
                        if (isRunning > 0) {
                            if (s[i] == 'A') {
                                //System.out.println ("DDD");
                                // end the segment
                                res += dp[(i + 1) & 1][cntA + 1][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA + 1, cntSegements, 0);

                                // continue;
                                res += dp[(i + 1) & 1][cntA + 1][seg][1];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA + 1, cntSegements, 1);
                            } else {
                                // end the segment
                                res += dp[(i + 1) & 1][cntA][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 0);

                                // continue;
                                res += dp[(i + 1) & 1][cntA][seg][1];
                                res %= mod;
                                // += dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 1);
                            }
                        } else {
                            // System.out.println ("DDDFFF");
                            // make a segment of just size equal to 1.
                            if (s[i] == 'A') {
                                if (seg + 1 <= 3) {
                                    // System.out.println ("LIFE");

                                    // begin and end the segment
                                    res += dp[(i + 1) & 1][cntA + 1][seg + 1][0];
                                    res %= mod;
                                    //+= dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA + 1, cntSegements + 1, 0);
                                }
                            } else {
                                if (seg + 1 <= 3) {
                                    // begin and end the segment
                                    res += dp[(i + 1) & 1][cntA][seg + 1][0];
                                    res %= mod;
                                    //+= dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA, cntSegements + 1, 0);
                                }
                            }

                            // do the remaining thing.
                            if (s[i] == 'A') {
                                if (seg + 1 <= 3) {
                                    // System.out.println ("WIFE");

                                    // begin the segment
                                    res += dp[(i + 1) & 1][cntA + 1][seg + 1][1];
                                    res %= mod;
                                    // += dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA + 1, cntSegements + 1, 1);
                                }
                                // System.out.println ("BANANA");

                                // continue;
                                res += dp[(i + 1) & 1][cntA][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 0);
                            } else {
                                if (seg + 1 <= 3) {
                                    // begin the segment
                                    res += dp[(i + 1) & 1][cntA][seg + 1][1];
                                    res %= mod;
                                    //+= dp[i][cntA][seg][isRunning];
                                    //res += dp (index + 1, cntA, cntSegements + 1, 1);
                                }
                                // continue;
                                res += dp[(i + 1) & 1][cntA][seg][0];
                                res %= mod;
                                //+= dp[i][cntA][seg][isRunning];
                                //res += dp (index + 1, cntA, cntSegements, 0);
                            }
                        }

                        //System.out.println ("Res " + res);
                        dp[i & 1][cntA][seg][isRunning] = res;
                    }
                }
            }
        }

        long ans = dp[1][0][0][0];

        return ans;
    }

    private static long bruteForce() {
        long ans = 0;
        for (int start1 = 1; start1 <= n; start1++) {
            for (int end1 = start1; end1 <= n; end1++) {
                for (int start2 = end1 + 1; start2 <= n; start2++) {
                    for (int end2 = start2; end2 <= n; end2++) {
                        for (int start3 = end2 + 1; start3 <= n; start3++) {
                            for (int end3 = start3; end3 <= n; end3++) {
                                int cnt = 0;
                                for (int i = start1; i <= end1; i++) {
                                    if (s[i] == 'A')
                                        cnt ++;
                                }
                                for (int i = start2; i <= end2; i++) {
                                    if (s[i] == 'A')
                                        cnt ++;
                                }
                                for (int i = start3; i <= end3; i++) {
                                    if (s[i] == 'A')
                                        cnt ++;
                                }

                                if (cnt >= requiredA) {
                                    ans ++;
                                }
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }

    private static int solve() {
        return 0;
    }


    private static long dp(int index, int cntA, int cntSegements, int isSegmentRunning) {
        if (memo[index][cntA][cntSegements][isSegmentRunning] != -1) {
            return memo[index][cntA][cntSegements][isSegmentRunning];
        }

        long res = 0;
        if (index == n + 1) {
            //System.out.println (cntSegements + " " + cntA + " " + requiredA + " " + isSegmentRunning);
            if (cntSegements == 3 && cntA >= requiredA && isSegmentRunning == 0) {
                res = 1;
            } else {
                res = 0;
            }
        } else {
            if (isSegmentRunning > 0) {
                if (s[index] == 'A') {
                    // end the segment
                    res += dp (index + 1, cntA + 1, cntSegements, 0);

                    // continue;
                    res += dp (index + 1, cntA + 1, cntSegements, 1);
                } else {
                    // end the segment
                    res += dp (index + 1, cntA, cntSegements, 0);

                    // continue;
                    res += dp (index + 1, cntA, cntSegements, 1);
                }
            } else {
                // make a segment of just size equal to 1.
                if (s[index] == 'A') {
                    if (cntSegements + 1 <= 3) {
                        // begin and end the segment
                        res += dp (index + 1, cntA + 1, cntSegements + 1, 0);
                    }
                } else {
                    if (cntSegements + 1 <= 3) {
                        // begin and end the segment
                        res += dp (index + 1, cntA, cntSegements + 1, 0);
                    }
                }

                // do the remaining thing.
                if (s[index] == 'A') {
                    if (cntSegements + 1 <= 3) {
                        // begin the segment
                        res += dp (index + 1, cntA + 1, cntSegements + 1, 1);
                    }
                    // continue;
                    res += dp (index + 1, cntA, cntSegements, 0);
                } else {
                    if (cntSegements + 1 <= 3) {
                        // begin the segment
                        res += dp (index + 1, cntA, cntSegements + 1, 1);
                    }
                    // continue;
                    res += dp (index + 1, cntA, cntSegements, 0);
                }
            }
        }

        res %= mod;

        memo[index][cntA][cntSegements][isSegmentRunning] = res;
        return res;
    }
}

