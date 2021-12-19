.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/BRA_Lib.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_strln PROTO : DWORD
_out PROTO : DWORD
_outInt PROTO : DWORD
_strcopy PROTO : BYTE, :BYTE
_strcon PROTO : BYTE, :BYTE


.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0
	L0 DWORD 5
	L1 DWORD 5
	L2 DWORD 2
	L3 DWORD 2
	L4 DWORD 6
	L5 BYTE '---', 0
	L6 BYTE '+', 0
	L7 BYTE '=', 0
	L8 BYTE '-', 0
	L9 BYTE '=', 0
	L10 BYTE '*', 0
	L11 BYTE '=', 0
	L12 BYTE '/', 0
	L13 BYTE '=', 0
	L14 BYTE '%', 0
	L15 BYTE '=', 0
	L16 BYTE 'two', 0
	L17 BYTE 'concat', 0
	L18 BYTE 'copy', 0
	L19 BYTE '2-', 0
	L20 BYTE 'length', 0
	L21 BYTE 'one', 0
	L22 DWORD 0
	L23 DWORD 0
	L24 DWORD 5
	L25 DWORD 0
.data
	_arithq		DWORD 0 ; int
	_arithw		DWORD 0 ; int
	_arithe		DWORD 0 ; int
	_arithr		DWORD 0 ; int
	_aritht		DWORD 0 ; int
	_fiuy		DWORD 0 ; str
	_fisome		DWORD 0 ; int
	_mainsr		DWORD 0 ; str
	_mainnum		DWORD 0 ; int
	_mainuj		DWORD 0 ; int

.code
_arith PROC _arithnum: DWORD
	push		L0
	pop			_arithq

	push		L1
	pop			_arithw

	push		L2
	pop			_arithe

	push		L3
	pop			_arithr

	push		L4
	pop			_aritht

	push		offset L5
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L6
	call		_out

	push		_arithq
	call		_outInt

	push		_arithnum
	push		_arithq

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_arithnum

	push		offset L7
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L5
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L8
	call		_out

	push		_arithw
	call		_outInt

	push		_arithnum
	push		_arithw

	pop		ebx
	pop		eax
	sub		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_arithnum

	push		offset L9
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L5
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L10
	call		_out

	push		_arithe
	call		_outInt

	push		_arithnum
	push		_arithe

	pop		ebx
	pop		eax
	imul		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_arithnum

	push		offset L11
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L5
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L12
	call		_out

	push		_arithr
	call		_outInt

	push		_arithnum
	push		_arithr

	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_arithnum

	push		offset L13
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L5
	call		_out

	push		_arithnum
	call		_outInt

	push		offset L14
	call		_out

	push		_aritht
	call		_outInt

	push		_arithnum
	push		_aritht

	pop		ebx
	pop		eax
	test		ebx, ebx
	jz		EXIT_DIV_ON_NULL
	cdq
	idiv		ebx
	jo		EXIT_OVERFLOW
	push		edx

	pop			_arithnum

	push		offset L15
	call		_out

	push		_arithnum
	call		_outInt



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	mov		eax, _arithnum
	ret		4
_arith ENDP

_fi PROC _fis: DWORD
	push		offset L16
	pop			_fiuy

	push		_fis
	call		_out

	push		offset L17
	call		_out

	push		_fis
	push		_fiuy
	call		_strcon
	push		eax
	pop			_fis

	push		_fis
	call		_out

	push		offset L18
	call		_out

	push		_fiuy
	push		_fis
	call		_strcopy
	push		eax
	pop			_fis

	push		_fis
	call		_out

	push		offset L19
	call		_out

	push		_fiuy
	call		_out

	push		offset L20
	call		_out

	push		_fis
	call		_strln
	push		eax
	pop			_fisome

	push		_fisome
	call		_outInt



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	mov		eax, _fis
	ret		4
_fi ENDP

main PROC
	push		offset L21
	pop			_mainsr

	push		L22
	pop			_mainnum

	push		L23
	pop			_mainuj

	push		_mainnum
	call		_outInt

	push		_mainsr
	call		_out

	push		_mainsr
	call		_fi
	push		eax
	pop			_mainsr

	push		_mainnum
	call		_arith
	push		eax
	pop			_mainnum


	mov	ecx, L24

cicle1:

	push ecx
	push		_mainnum
	call		_outInt

	pop ecx
loop cicle1

	push		_mainuj
	call		_outInt



	jmp EXIT
EXIT_DIV_ON_NULL:
	push offset _DIVISION_BY_ZERO_ERROR
	call _out
	push -1
	call ExitProcess

EXIT_OVERFLOW:
	push offset _OVERFLOW_ERROR
	call _out
	push -2
	call ExitProcess

EXIT:
	push		L25
	call		ExitProcess

main ENDP
end main
