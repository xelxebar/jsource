NB. B *: B ---------------------------------------------------------------

x=: ?100$2
y=: ?100$2
(x*:y) -: (#.x,.y){1 1 1 0
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:?2
(x*:z) -: x*:($x)$z    [ z=:?2

(x*:y) -: (40$"0 x)*:y [ x=: ?10$2    [ y=: ?10 40$2
(x*:y) -: x*:40$"0 y   [ x=: ?10 40$2 [ y=: ?10$2

1 1 1 0 -: 0 0 1 1 *: 0 1 0 1


NB. B *: I ---------------------------------------------------------------

x=: ?100$2
y=: 2|?100$2e5
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:?2
(x*:z) -: x*:($x)$z    [ z=:2|?2e5

(x*:y) -: (40$"0 x)*:y [ x=: ?10$2    [ y=: 2|?10 40$2e5
(x*:y) -: x*:40$"0 y   [ x=: ?10 40$2 [ y=: 2|?10$2e5

1 1 1 0 -: 0 0 1 1 *: 0 1 0 1+4-4


NB. B *: D ---------------------------------------------------------------

x=: ?100$2
y=: [&.o.2|?100$2e5
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:?2
(x*:z) -: x*:($x)$z    [ z=:[&.o.2|?2e5

(x*:y) -: (40$"0 x)*:y [ x=: ?10$2    [ y=: [&.o.2|?10 40$2e5
(x*:y) -: x*:40$"0 y   [ x=: ?10 40$2 [ y=: [&.o.2|?10$2e5

1 1 1 0 -: 0 0 1 1 *: 0 1 0 1+3.5-3.5


NB. I *: B ---------------------------------------------------------------

x=: 2|?100$2e5
y=: ?100$2
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:2|?2e5
(x*:z) -: x*:($x)$z    [ z=:?2

(x*:y) -: (40$"0 x)*:y [ x=: 2|?10$2e5    [ y=: ?10 40$2
(x*:y) -: x*:40$"0 y   [ x=: 2|?10 40$2e5 [ y=: ?10$2

1 1 1 0 -: (0 0 1 1+3-3) *: 0 1 0 1


NB. I *: I ---------------------------------------------------------------

x=: 2|?100$2e5
y=: 2|?100$2e5
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:2|?2e6
(x*:z) -: x*:($x)$z    [ z=:2|?2e5

(x*:y) -: (40$"0 x)*:y [ x=: 2|?10$2e5    [ y=: 2|?10 40$2e5
(x*:y) -: x*:40$"0 y   [ x=: 2|?10 40$2e5 [ y=: 2|?10$2e5

1 1 1 0 -: (0 0 1 1+3-3) *: 0 1 0 1+3-3


NB. I *: D ---------------------------------------------------------------

x=: 2|?100$2e5
y=: [&.o.2|?100$2e5
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:2|?2e6
(x*:z) -: x*:($x)$z    [ z=:[&.o.2|?2e5

(x*:y) -: (40$"0 x)*:y [ x=: 2|?10$2e5    [ y=: [&.o.2|?10 40$2e5
(x*:y) -: x*:40$"0 y   [ x=: 2|?10 40$2e5 [ y=: [&.o.2|?10$2e5

1 1 1 0 -: (0 0 1 1+3-3) *: 0 1 0 1+3.4-3.4


NB. D *: B ---------------------------------------------------------------

x=: [&.o.2|?100$2e5
y=: ?100$2
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:[&.o.2|?2e5
(x*:z) -: x*:($x)$z    [ z=:?2

(x*:y) -: (40$"0 x)*:y [ x=: [&.o.2|?10$2e5    [ y=: ?10 40$2
(x*:y) -: x*:40$"0 y   [ x=: [&.o.2|?10 40$2e5 [ y=: ?10$2

1 1 1 0 -: (0 0 1 1+3.4-3.4) *: 0 1 0 1


NB. D *: I ---------------------------------------------------------------

x=: [&.o.2|?100$2e5
y=: 2|?100$2e5
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:[&.o.2|?2e5
(x*:z) -: x*:($x)$z    [ z=:2|?2e5

(x*:y) -: (40$"0 x)*:y [ x=: [&.o.2|?10$2e5    [ y=: 2|?10 40$2e5
(x*:y) -: x*:40$"0 y   [ x=: [&.o.2|?10 40$2e5 [ y=: 2|?10$2e5

1 1 1 0 -: (0 0 1 1+3.4-3.4) *: 0 1 0 1+34-34


NB. D *: D ---------------------------------------------------------------

x=: [&.o.2|?100$2e5
y=: [&.o.2|?100$2e5
(x*:y) -: (z+x)*:z+y   [ z=:{.0 4.5
(x*:y) -: (z*x)*:z*y   [ z=:{.1 4j5
(z*:y) -: (($y)$z)*:y  [ z=:[&.o.2|?2e5
(x*:z) -: x*:($x)$z    [ z=:[&.o.2|?2e5

(x*:y) -: (40$"0 x)*:y [ x=: [&.o.2|?10$2e5    [ y=: [&.o.2|?10 40$2e5
(x*:y) -: x*:40$"0 y   [ x=: [&.o.2|?10 40$2e5 [ y=: [&.o.2|?10$2e5

1 1 1 0 -: (0 0 1 1+3.4-3.4) *: 0 1 0 1+3.4-3.4

4!:55 ;:'x y z'


