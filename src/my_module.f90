module my_module
    USE, INTRINSIC :: ISO_C_Binding
    implicit none
    public :: add, mult
    contains
    
    subroutine add(a, b, res) BIND (C, NAME='add')
        IMPLICIT NONE
        real, intent(in) :: a, b
        real, intent(out) :: res

        res = a + b
    end subroutine add
    
    subroutine mult(a, b, res) BIND (C, NAME='mult')
        IMPLICIT NONE
        real, intent(in) :: a, b
        real, intent(out) :: res

        res = a * b
    end subroutine mult
    
    subroutine fat(n, f) BIND (C, NAME='fat')
        IMPLICIT NONE
        integer, intent(in) :: n
        integer, intent(out) :: f
        integer :: j
        
        if (n < 1) then
            f = 1
        else
            f = n
            do j=2, n-1
                f = f * j
            enddo
        endif
    end subroutine fat

end module my_module