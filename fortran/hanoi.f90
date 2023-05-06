program hanoi
  implicit none
  integer :: n, i
  character*30 :: char
  n = iargc()
  if (n.EQ.1) then
    call getarg(1, char)
    read(char, "(i30)") i
    call move(i, 'A', 'B', 'C')
  else
    print *, "usage hanoi <number>"
  end if
end program

recursive subroutine move(n, from, mid, to)
  integer :: n
  character :: from, mid, to
  if (n.EQ.1) then
    print *, from, "->", to
  else
    call move(n-1, from, to, mid)
    call move(1, from, mid, to)
    call move(n-1, mid, from, to)
  end if
end subroutine

