module my_module
    USE, INTRINSIC :: ISO_C_Binding
    implicit none
    public :: add, mult
    contains
    
    subroutine add(a, b, result) BIND (C, NAME='add')
        IMPLICIT NONE
        real, intent(in) :: a, b
        real, intent(out) :: result

        result = a + b
    end subroutine add
    
    subroutine mult(a, b, result) BIND (C, NAME='mult')
        IMPLICIT NONE
        real, intent(in) :: a, b
        real, intent(out) :: result

        result = a * b
    end subroutine mult

end module my_module