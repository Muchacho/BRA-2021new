.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/BRA_Lib.lib
ExitProcess PROTO : DWORD
_compare PROTO : DWORD, :DWORD
_strln PROTO : BYTE
_out PROTO : DWORD
_outInt PROTO : DWORD
_concatstr PROTO : DWORD, :DWORD

.stack 4096
.const
	_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0
	_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0
	L0 DWORD 5
	L1 BYTE 'sdf', 0
	L2 BYTE '3', 0
	L3 BYTE 'qwe', 0
	L4 BYTE 'asd', 0
	L5 DWORD 10
	L6 DWORD 5
	L7 DWORD 0
.data
	_fia		DWORD 0 ; int
	_fih		DWORD 0 ; str
	_fid		DWORD 0 ; int
	_mainz		DWORD 0 ; int
	_mains		DWORD 0 ; str
	_maing		DWORD 0 ; str

.code
_fi PROC _fix: DWORD
	push		L0
	pop			_fia

	push		offset L1
	pop			_fih

	push		offset L2
	pop			_fid

	push		_fia
	call		_outInt

	push		_fid
	call		_out

	push		_fih
	call		_out

	push		_fia
	push		_fix

	pop		eax
	pop		ebx
	add		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_fia

	push		_fia
	call		_outInt

	push		_fih
	call		_strln
	push		eax
	pop			_fia

	push		_fia
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
	mov		eax, _fia
	ret		4
_fi ENDP

main PROC
	push		offset L3
	pop			_mains

	push		offset L4
	pop			_maing

	push		_mains
	call		_out

	push		_maing
	call		_out

	push		_mainz
	call		_fi
	push		eax
	pop			_mainz

	push		_mains
	call		_out

	push		_mainz
	call		_outInt

	push		L5
	push		L6

	pop		ebx
	pop		eax
	sub		eax, ebx
	jo		EXIT_OVERFLOW
	push		eax

	pop			_mainz

	push		_mainz
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
	push		L7
	call		ExitProcess

main ENDP
end main
