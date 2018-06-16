# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected (IGNORE_EXIT_CODES => 1, [<<'EOF']);
(syn-read-max) begin
(syn-read-max) create "data"
(syn-read-max) open "data"
(syn-read-max) write "data"
(syn-read-max) close "data"
(syn-read-max) exec child 1 of 50: "child-syn-read 0"
(syn-read-max) exec child 2 of 50: "child-syn-read 1"
(syn-read-max) exec child 3 of 50: "child-syn-read 2"
(syn-read-max) exec child 4 of 50: "child-syn-read 3"
(syn-read-max) exec child 5 of 50: "child-syn-read 4"
(syn-read-max) exec child 6 of 50: "child-syn-read 5"
(syn-read-max) exec child 7 of 50: "child-syn-read 6"
(syn-read-max) exec child 8 of 50: "child-syn-read 7"
(syn-read-max) exec child 9 of 50: "child-syn-read 8"
(syn-read-max) exec child 10 of 50: "child-syn-read 9"
(syn-read-max) exec child 11 of 50: "child-syn-read 10"
(syn-read-max) exec child 12 of 50: "child-syn-read 11"
(syn-read-max) exec child 13 of 50: "child-syn-read 12"
(syn-read-max) exec child 14 of 50: "child-syn-read 13"
(syn-read-max) exec child 15 of 50: "child-syn-read 14"
(syn-read-max) exec child 16 of 50: "child-syn-read 15"
(syn-read-max) exec child 17 of 50: "child-syn-read 16"
(syn-read-max) exec child 18 of 50: "child-syn-read 17"
(syn-read-max) exec child 19 of 50: "child-syn-read 18"
(syn-read-max) exec child 20 of 50: "child-syn-read 19"
(syn-read-max) exec child 21 of 50: "child-syn-read 20"
(syn-read-max) exec child 22 of 50: "child-syn-read 21"
(syn-read-max) exec child 23 of 50: "child-syn-read 22"
(syn-read-max) exec child 24 of 50: "child-syn-read 23"
(syn-read-max) exec child 25 of 50: "child-syn-read 24"
(syn-read-max) exec child 26 of 50: "child-syn-read 25"
(syn-read-max) exec child 27 of 50: "child-syn-read 26"
(syn-read-max) exec child 28 of 50: "child-syn-read 27"
(syn-read-max) exec child 29 of 50: "child-syn-read 28"
(syn-read-max) exec child 30 of 50: "child-syn-read 29"
(syn-read-max) exec child 31 of 50: "child-syn-read 30"
(syn-read-max) exec child 32 of 50: "child-syn-read 31"
(syn-read-max) exec child 33 of 50: "child-syn-read 32"
(syn-read-max) exec child 34 of 50: "child-syn-read 33"
(syn-read-max) exec child 35 of 50: "child-syn-read 34"
(syn-read-max) exec child 36 of 50: "child-syn-read 35"
(syn-read-max) exec child 37 of 50: "child-syn-read 36"
(syn-read-max) exec child 38 of 50: "child-syn-read 37"
(syn-read-max) exec child 39 of 50: "child-syn-read 38"
(syn-read-max) exec child 40 of 50: "child-syn-read 39"
(syn-read-max) exec child 41 of 50: "child-syn-read 40"
(syn-read-max) exec child 42 of 50: "child-syn-read 41"
(syn-read-max) exec child 43 of 50: "child-syn-read 42"
(syn-read-max) exec child 44 of 50: "child-syn-read 43"
(syn-read-max) exec child 45 of 50: "child-syn-read 44"
(syn-read-max) exec child 46 of 50: "child-syn-read 45"
(syn-read-max) exec child 47 of 50: "child-syn-read 46"
(syn-read-max) exec child 48 of 50: "child-syn-read 47"
(syn-read-max) exec child 49 of 50: "child-syn-read 48"
(syn-read-max) exec child 50 of 50: "child-syn-read 49"
(syn-read-max) wait for child 1 of 50 returned 0 (expected 0)
(syn-read-max) wait for child 2 of 50 returned 1 (expected 1)
(syn-read-max) wait for child 3 of 50 returned 2 (expected 2)
(syn-read-max) wait for child 4 of 50 returned 3 (expected 3)
(syn-read-max) wait for child 5 of 50 returned 4 (expected 4)
(syn-read-max) wait for child 6 of 50 returned 5 (expected 5)
(syn-read-max) wait for child 7 of 50 returned 6 (expected 6)
(syn-read-max) wait for child 8 of 50 returned 7 (expected 7)
(syn-read-max) wait for child 9 of 50 returned 8 (expected 8)
(syn-read-max) wait for child 10 of 50 returned 9 (expected 9)
(syn-read-max) wait for child 11 of 50 returned 10 (expected 10)
(syn-read-max) wait for child 12 of 50 returned 11 (expected 11)
(syn-read-max) wait for child 13 of 50 returned 12 (expected 12)
(syn-read-max) wait for child 14 of 50 returned 13 (expected 13)
(syn-read-max) wait for child 15 of 50 returned 14 (expected 14)
(syn-read-max) wait for child 16 of 50 returned 15 (expected 15)
(syn-read-max) wait for child 17 of 50 returned 16 (expected 16)
(syn-read-max) wait for child 18 of 50 returned 17 (expected 17)
(syn-read-max) wait for child 19 of 50 returned 18 (expected 18)
(syn-read-max) wait for child 20 of 50 returned 19 (expected 19)
(syn-read-max) wait for child 21 of 50 returned 20 (expected 20)
(syn-read-max) wait for child 22 of 50 returned 21 (expected 21)
(syn-read-max) wait for child 23 of 50 returned 22 (expected 22)
(syn-read-max) wait for child 24 of 50 returned 23 (expected 23)
(syn-read-max) wait for child 25 of 50 returned 24 (expected 24)
(syn-read-max) wait for child 26 of 50 returned 25 (expected 25)
(syn-read-max) wait for child 27 of 50 returned 26 (expected 26)
(syn-read-max) wait for child 28 of 50 returned 27 (expected 27)
(syn-read-max) wait for child 29 of 50 returned 28 (expected 28)
(syn-read-max) wait for child 30 of 50 returned 29 (expected 29)
(syn-read-max) wait for child 31 of 50 returned 30 (expected 30)
(syn-read-max) wait for child 32 of 50 returned 31 (expected 31)
(syn-read-max) wait for child 33 of 50 returned 32 (expected 32)
(syn-read-max) wait for child 34 of 50 returned 33 (expected 33)
(syn-read-max) wait for child 35 of 50 returned 34 (expected 34)
(syn-read-max) wait for child 36 of 50 returned 35 (expected 35)
(syn-read-max) wait for child 37 of 50 returned 36 (expected 36)
(syn-read-max) wait for child 38 of 50 returned 37 (expected 37)
(syn-read-max) wait for child 39 of 50 returned 38 (expected 38)
(syn-read-max) wait for child 40 of 50 returned 39 (expected 39)
(syn-read-max) wait for child 41 of 50 returned 40 (expected 40)
(syn-read-max) wait for child 42 of 50 returned 41 (expected 41)
(syn-read-max) wait for child 43 of 50 returned 42 (expected 42)
(syn-read-max) wait for child 44 of 50 returned 43 (expected 43)
(syn-read-max) wait for child 45 of 50 returned 44 (expected 44)
(syn-read-max) wait for child 46 of 50 returned 45 (expected 45)
(syn-read-max) wait for child 47 of 50 returned 46 (expected 46)
(syn-read-max) wait for child 48 of 50 returned 47 (expected 47)
(syn-read-max) wait for child 49 of 50 returned 48 (expected 48)
(syn-read-max) wait for child 50 of 50 returned 49 (expected 49)
(syn-read-max) end
EOF
pass;
