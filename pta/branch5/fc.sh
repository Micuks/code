./pt6 < data.in > my.out
./stdpt6 < data.in > std.out
if diff my.out std.out ; then
    printf "AC\n"
else
    printf "WA\n"
    exit 0;
fi