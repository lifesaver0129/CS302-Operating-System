# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(rox-maxchild) begin
(rox-maxchild) open "child-rox"
(rox-maxchild) read "child-rox"
(rox-maxchild) write "child-rox"
(rox-maxchild) exec "child-rox 10"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 9"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 8"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 7"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 6"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 5"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 4"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 3"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 2"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) exec "child-rox 1"
(child-rox) begin
(child-rox) try to write "child-rox"
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(child-rox) try to write "child-rox"
(child-rox) end
child-rox: exit(12)
(rox-maxchild) write "child-rox"
(rox-maxchild) end
rox-maxchild: exit(0)
EOF
pass;
