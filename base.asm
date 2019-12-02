;INCOMPLETO

#start=robot.exe#

name "robot"

#make_bin#
#cs = 500#
#ds = 500#
#ss = 500#    ; stack
#sp = ffff#
#ip = 0#

; robot base i/o port:
r_port equ 9

;===================================
; this procedure does not
; return until robot is ready
; to receive next command:
espera_robo proc
; check if robot busy:
busy: in al, r_port+2
      test al, 00000010b
      jnz busy ; busy, so wait.
ret    
espera_robo endp

;===================================

; this procedure does not
; return until robot completes
; the examination:
espera_exame proc
; check if has new data:
busy2: in al, r_port+2
       test al, 00000001b
       jz busy2 ; no new data, so wait.
ret    
espera_exame endp

;===================================

; switch off the lamp:
apaga_lampada proc
mov al, 6
out r_port, al
ret
apaga_lampada endp

;===================================

; switch on the lamp:
acende_lampada proc
mov al, 5
out r_port, al
ret
acende_lampada endp

;===================================

examina proc
mov al, 4
out r_port, al
call espera_exame
ret
examina endp

;===================================

vira_direita proc
mov al, 3
out r_port, al
ret
vira_direita endp

;===================================

vira_esquerda proc
mov al, 2
out r_port, al
ret
vira_esquerda endp

;===================================

move proc
mov al, 1
out r_port, al
ret
move endp

;===================================

robo_pronto proc
in al, r_port+2
test al, 00000111b
ret
robo_pronto endp

;===================================

robo_ocupado proc
in al, r_port+2
test al, 00000100b
ret
robo_pronto endp

;===================================

robo_parado proc
in al, r_port+2
test al, 00000110b
ret
robo_pronto endp
