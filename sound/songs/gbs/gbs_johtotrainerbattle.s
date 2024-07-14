	.include "asm/macros.inc"

	.section .rodata
	.align 1

gbs_johtotrainerbattle_Ch1:
	gbs_switch 0
	tempo 102
	volume 7, 7
	duty_cycle 3
	pitch_offset 2
	vibrato 18, 1, 5
	note_type 12, 9, 2
	rest 8
	octave 3
	note A_, 1
	note Gs, 1
	note G_, 1
	note Gs, 1
	volume_envelope 11, 2
	note C_, 1
	octave 2
	note B_, 1
	note As, 1
	note B_, 1
	octave 3
	note Cs, 1
	note C_, 1
	octave 2
	note B_, 1
	octave 3
	note C_, 1
	note D_, 1
	note Cs, 1
	note C_, 1
	note Cs, 1
	note Ds, 1
	note D_, 1
	note Cs, 1
	note D_, 1
	note E_, 1
	note Ds, 1
	note D_, 1
	note Ds, 1
	note E_, 6
	note E_, 6
	note E_, 4
	note E_, 2
	note D_, 2
	note E_, 2
	note F_, 6
	volume_envelope 11, 7
	note D_, 4
	volume_envelope 11, 2
	note E_, 6
	note D_, 6
	note E_, 4
	note E_, 2
	note D_, 2
	note E_, 2
	note F_, 6
	volume_envelope 11, 7
	note F_, 4
	volume_envelope 11, 2
	octave 4
	note E_, 6
	note E_, 6
	note E_, 4
	note E_, 2
	note D_, 2
	note E_, 2
	note F_, 2
	octave 3
	note A_, 2
	note As, 2
	volume_envelope 11, 7
	note B_, 4
	volume_envelope 11, 2
	octave 4
	note E_, 6
	note E_, 6
	note E_, 4
	note E_, 2
	note D_, 2
	note E_, 2
	note F_, 6
	volume_envelope 11, 7
	note G_, 4
gbs_johtotrainerbattle_Ch1.mainloop:
	volume_envelope 11, 4
	sound_call gbs_johtotrainerbattle_Ch1.sub1
	volume_envelope 11, 7
	note As, 4
	volume_envelope 11, 3
	note G_, 1
	note F_, 1
	note E_, 1
	note G_, 1
	volume_envelope 11, 7
	octave 4
	note C_, 4
	volume_envelope 11, 3
	octave 3
	note A_, 1
	note G_, 1
	note F_, 1
	note A_, 1
	volume_envelope 11, 7
	octave 4
	note D_, 4
	volume_envelope 11, 3
	note C_, 1
	octave 3
	note As, 1
	note A_, 1
	octave 4
	note C_, 1
	volume_envelope 11, 5
	note F_, 2
	note E_, 2
	note D_, 2
	note C_, 2
	sound_call gbs_johtotrainerbattle_Ch1.sub1
	volume_envelope 11, 7
	note F_, 4
	note E_, 2
	note F_, 2
	octave 4
	note C_, 4
	octave 3
	note As, 2
	octave 4
	note C_, 2
	volume_envelope 10, 0
	octave 3
	note F_, 8
	volume_envelope 10, 7
	note F_, 8
	volume_envelope 11, 7
	note A_, 6
	note E_, 6
	note As, 4
	octave 4
	note Cs, 6
	note F_, 4
	note E_, 2
	note D_, 2
	note F_, 2
	note E_, 2
	note F_, 2
	note E_, 2
	note D_, 2
	note Cs, 2
	octave 3
	note As, 2
	note A_, 2
	note As, 2
	volume_envelope 10, 0
	note A_, 8
	volume_envelope 10, 7
	note A_, 8
	volume_envelope 11, 7
	note E_, 8
	note D_, 8
	note E_, 8
	note F_, 8
	note E_, 8
	note D_, 8
	note G_, 8
	note F_, 8
	note D_, 8
	note C_, 8
	note D_, 8
	note Ds, 8
	note D_, 8
	note C_, 8
	note D_, 8
	note Ds, 8
	note D_, 8
	note Ds, 8
	note E_, 8
	note F_, 8
	volume_envelope 11, 4
	note G_, 2
	octave 4
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 2
	note F_, 2
	note Ds, 2
	note F_, 2
	note G_, 2
	octave 4
	note Cs, 2
	note C_, 2
	note Cs, 2
	note Ds, 2
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
	volume_envelope 11, 5
	note Ds, 2
	note D_, 2
	volume_envelope 11, 2
	note Ds, 4
	volume_envelope 11, 7
	note C_, 8
	note Ds, 4
	note Cs, 4
	note C_, 4
	note Ds, 4
	volume_envelope 11, 5
	note E_, 2
	note Ds, 2
	volume_envelope 11, 2
	note E_, 4
	volume_envelope 11, 7
	note Cs, 8
	note F_, 4
	note Ds, 4
	note Cs, 4
	note F_, 4
	volume_envelope 11, 5
	note Fs, 2
	note F_, 2
	volume_envelope 11, 2
	note Fs, 4
	volume_envelope 11, 7
	note D_, 8
	note Fs, 4
	note E_, 4
	note D_, 4
	note Fs, 4
	note G_, 8
	note Ds, 8
	note As, 8
	note G_, 8
	volume_envelope 10, 0
	note Ds, 4
	volume_envelope 10, 7
	note Ds, 12
	rest 16
gbs_johtotrainerbattle_Ch1.loop1:
	volume_envelope 11, 7
	note F_, 8
	volume_envelope 11, 4
	note G_, 4
	note Ds, 4
	note F_, 4
	note G_, 2
	note Ds, 2
	note F_, 4
	octave 2
	note As, 4
	volume_envelope 11, 7
	octave 3
	note F_, 8
	volume_envelope 11, 4
	note G_, 4
	note Ds, 4
	note F_, 4
	note G_, 2
	note Ds, 2
	note F_, 4
	note F_, 4
	sound_loop 2, gbs_johtotrainerbattle_Ch1.loop1
	volume_envelope 11, 7
	note F_, 8
	volume_envelope 11, 4
	note G_, 4
	note Ds, 4
	note F_, 4
	note Gs, 2
	note G_, 2
	volume_envelope 11, 7
	note F_, 8
	note F_, 8
	volume_envelope 11, 5
	note G_, 4
	note Ds, 4
	note F_, 4
	note G_, 2
	note Ds, 2
	volume_envelope 11, 7
	note F_, 8
	note F_, 8
	volume_envelope 11, 5
	note G_, 4
	note Ds, 4
	note F_, 4
	note G_, 2
	note Ds, 2
	volume_envelope 3, -7
	note Gs, 8
	volume_envelope 11, 7
	note Gs, 8
	volume_envelope 10, 0
	octave 4
	note C_, 8
	volume_envelope 10, 7
	note C_, 8
	volume_envelope 11, 2
	octave 3
	note Ds, 6
	note Ds, 6
	note Ds, 4
	note Ds, 6
	note Ds, 6
	volume_envelope 11, 7
	note F_, 4
	volume_envelope 11, 2
	note Ds, 6
	note Ds, 6
	note Ds, 4
	note Ds, 6
	note Ds, 6
	volume_envelope 4, -4
	note F_, 4
	volume_envelope 11, 7
	note Gs, 6
	note G_, 6
	note F_, 4
	note Ds, 4
	note F_, 4
	note G_, 4
	note Ds, 4
	note F_, 4
	octave 4
	note Cs, 2
	note C_, 2
	octave 3
	note F_, 4
	octave 4
	note Cs, 2
	note C_, 2
	octave 3
	note F_, 2
	note G_, 2
	note Gs, 2
	octave 4
	note C_, 2
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 6
	note Ds, 6
	note G_, 4
	octave 4
	note Cs, 4
	note C_, 4
	octave 3
	note As, 4
	note Gs, 4
	note F_, 4
	note Cs, 2
	note Ds, 2
	note F_, 4
	note Cs, 2
	note Ds, 2
	note As, 4
	note Gs, 4
	note G_, 4
	note F_, 4
	volume_envelope 9, 0
	octave 2
	note As, 8
	octave 3
	note Ds, 8
	octave 2
	note As, 8
	octave 3
	note G_, 8
	volume_envelope 10, 0
	note Ds, 8
	note As, 8
	note G_, 8
	octave 4
	note Ds, 8
	volume_envelope 10, 0
	octave 3
	note As, 8
	volume_envelope 10, 7
	note As, 8
	volume_envelope 11, 7
	note G_, 6
	note As, 6
	note Gs, 2
	note G_, 2
	volume_envelope 10, 0
	note Ds, 8
	volume_envelope 10, 7
	note Ds, 8
	volume_envelope 11, 4
	note As, 6
	note G_, 4
	note G_, 2
	note As, 12
	rest 16
	rest 8
	volume_envelope 10, 0
	octave 4
	note D_, 4
	volume_envelope 10, 7
	note D_, 12
	volume_envelope 10, 0
	note F_, 8
	volume_envelope 10, 7
	note F_, 8
	volume_envelope 11, 3
	sound_call gbs_johtotrainerbattle_Ch1.sub1
	note F_, 4
	note E_, 2
	note F_, 2
	octave 4
	note C_, 4
	octave 3
	note As, 2
	octave 4
	note C_, 2
	volume_envelope 10, 0
	octave 3
	note F_, 10
	volume_envelope 10, 7
	note F_, 6
	sound_loop 0, gbs_johtotrainerbattle_Ch1.mainloop

gbs_johtotrainerbattle_Ch1.sub1:
	octave 3
	note E_, 2
	note D_, 2
	note E_, 2
	note A_, 2
	note B_, 2
	note A_, 2
	note G_, 2
	note A_, 2
	octave 4
	note C_, 2
	octave 3
	note A_, 2
	note B_, 2
	note G_, 2
	note A_, 2
	note E_, 2
	note F_, 2
	note D_, 2
	sound_ret

gbs_johtotrainerbattle_Ch2:
	gbs_switch 1
	duty_cycle 3
	vibrato 8, 3, 6
	pitch_offset 1
	note_type 12, 12, 2
	octave 4
	note Gs, 1
	note G_, 1
	note Fs, 1
	note F_, 1
	note Gs, 1
	note D_, 1
	note Ds, 1
	note E_, 1
	note Gs, 1
	note Ds, 1
	note D_, 1
	note Ds, 1
	note Gs, 1
	note D_, 1
	note Cs, 1
	note D_, 1
	note Gs, 1
	note Cs, 1
	note C_, 1
	note Cs, 1
	note Gs, 1
	octave 3
	note As, 1
	note B_, 1
	octave 4
	note C_, 1
	note Gs, 1
	octave 3
	note B_, 1
	note As, 1
	note B_, 1
	octave 4
	note Gs, 1
	octave 3
	note As, 1
	note A_, 1
	note As, 1
	volume_envelope 12, 2
	octave 4
	note A_, 6
	sound_call gbs_johtotrainerbattle_Ch2.sub1
	volume_envelope 12, 2
	note A_, 6
	sound_call gbs_johtotrainerbattle_Ch2.sub1
	volume_envelope 12, 2
	octave 5
	note C_, 6
	note C_, 6
	note C_, 4
	note C_, 6
	note C_, 6
	volume_envelope 12, 7
	note Cs, 4
	volume_envelope 12, 2
	note C_, 2
	volume_envelope 10, 4
	octave 3
	note E_, 2
	note A_, 2
	volume_envelope 12, 2
	octave 5
	note C_, 2
	volume_envelope 10, 4
	octave 3
	note E_, 2
	note A_, 2
	volume_envelope 12, 2
	octave 5
	note C_, 2
	volume_envelope 10, 4
	octave 3
	note E_, 2
	volume_envelope 12, 2
	octave 5
	note C_, 2
	volume_envelope 10, 4
	octave 3
	note E_, 2
	note B_, 2
	volume_envelope 12, 2
	octave 5
	note C_, 2
	volume_envelope 10, 4
	octave 4
	note C_, 2
	note E_, 2
	volume_envelope 12, 7
	note B_, 4
gbs_johtotrainerbattle_Ch2.mainloop:
	sound_call gbs_johtotrainerbattle_Ch2.sub2
	volume_envelope 3, -6
	note As, 8
	volume_envelope 12, 7
	note As, 8
	sound_call gbs_johtotrainerbattle_Ch2.sub2
	volume_envelope 12, 4
	note D_, 4
	octave 3
	note As, 2
	octave 4
	note D_, 2
	note F_, 2
	note E_, 2
	note D_, 2
	note F_, 2
	note E_, 2
	note D_, 2
	note E_, 2
	note F_, 2
	note As, 2
	note A_, 2
	note As, 2
	octave 5
	note D_, 2
	volume_envelope 11, 0
	note Cs, 8
	volume_envelope 11, 7
	note Cs, 4
	volume_envelope 12, 7
	octave 4
	note As, 4
	volume_envelope 11, 0
	note A_, 16
	volume_envelope 11, 7
	note A_, 16
gbs_johtotrainerbattle_Ch2.loop1:
	volume_envelope 12, 3
	octave 3
	note A_, 2
	note G_, 2
	note A_, 2
	volume_envelope 12, 7
	note As, 4
	volume_envelope 12, 3
	note A_, 2
	note G_, 2
	note As, 2
	sound_loop 3, gbs_johtotrainerbattle_Ch2.loop1
	note A_, 2
	octave 4
	note D_, 2
	note C_, 2
	octave 3
	note As, 2
	note A_, 2
	note G_, 2
	note A_, 2
	note As, 2
gbs_johtotrainerbattle_Ch2.loop2:
	note G_, 2
	note F_, 2
	note G_, 2
	volume_envelope 12, 7
	note Gs, 4
	volume_envelope 12, 3
	note G_, 2
	note F_, 2
	note Gs, 2
	sound_loop 3, gbs_johtotrainerbattle_Ch2.loop2
	note F_, 2
	octave 4
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 2
	note F_, 2
	note G_, 2
	note Gs, 2
	volume_envelope 12, 7
	note G_, 6
	octave 4
	note D_, 6
	note C_, 2
	note D_, 2
	note F_, 4
	note E_, 4
	note D_, 4
	note C_, 4
	volume_envelope 11, 0
	note Ds, 10
	volume_envelope 11, 7
	note Ds, 6
	volume_envelope 9, 0
	note G_, 8
	volume_envelope 9, 7
	note G_, 8
	volume_envelope 12, 7
	octave 3
	note F_, 8
	note Ds, 4
	note F_, 4
	note G_, 4
	note F_, 4
	note Ds, 4
	note G_, 4
	note Gs, 8
	note F_, 4
	note G_, 4
	note Gs, 4
	note G_, 4
	note F_, 4
	note Gs, 4
	note A_, 8
	note Fs, 4
	note Gs, 4
	note A_, 4
	note Gs, 4
	note Fs, 4
	note A_, 4
	volume_envelope 11, 0
	note As, 8
	note As, 8
	volume_envelope 11, 0
	octave 4
	note Ds, 8
	volume_envelope 11, 7
	note Ds, 8
	volume_envelope 6, 2
	sound_call gbs_johtotrainerbattle_Ch2.sub3
	volume_envelope 8, 2
	sound_call gbs_johtotrainerbattle_Ch2.sub3
	volume_envelope 9, 2
	sound_call gbs_johtotrainerbattle_Ch2.sub3
	volume_envelope 10, 2
	sound_call gbs_johtotrainerbattle_Ch2.sub3
gbs_johtotrainerbattle_Ch2.loop3:
	octave 4
	note Ds, 2
	octave 3
	note As, 2
	octave 4
	note G_, 2
	octave 3
	note As, 2
	octave 4
	note Ds, 2
	octave 3
	note As, 2
	octave 4
	note G_, 2
	octave 3
	note As, 2
	sound_loop 8, gbs_johtotrainerbattle_Ch2.loop3
	sound_call gbs_johtotrainerbattle_Ch2.sub4
	octave 3
	note As, 2
	volume_envelope 12, 7
	octave 4
	note C_, 8
	sound_call gbs_johtotrainerbattle_Ch2.sub4
	note G_, 2
	volume_envelope 12, 7
	note F_, 8
	sound_call gbs_johtotrainerbattle_Ch2.sub4
	octave 3
	note As, 2
	volume_envelope 11, 0
	octave 4
	note C_, 8
	volume_envelope 11, 7
	note C_, 8
	volume_envelope 1, -7
	note Ds, 12
	volume_envelope 12, 7
	note Ds, 4
	volume_envelope 12, 2
	octave 3
	note G_, 4
	note Ds, 2
	note G_, 6
	note G_, 4
	note G_, 2
	note F_, 2
	note Ds, 2
	note G_, 6
	volume_envelope 12, 7
	note Gs, 4
	volume_envelope 12, 2
	note G_, 4
	note Ds, 2
	note G_, 6
	note G_, 4
	note G_, 6
	note G_, 6
	volume_envelope 4, -4
	note Gs, 4
	sound_call gbs_johtotrainerbattle_Ch2.sub5
	volume_envelope 11, 0
	note F_, 8
	volume_envelope 11, 7
	note F_, 8
	volume_envelope 11, 0
	note Gs, 8
	volume_envelope 11, 7
	note Gs, 8
	sound_call gbs_johtotrainerbattle_Ch2.sub5
	volume_envelope 11, 0
	note Cs, 8
	volume_envelope 11, 7
	note Cs, 8
	volume_envelope 12, 7
	note Cs, 4
	note C_, 4
	octave 3
	note As, 4
	note Gs, 4
	note G_, 6
	note Ds, 2
	note As, 8
	note As, 6
	note G_, 2
	octave 4
	note Ds, 8
	note Ds, 6
	octave 3
	note As, 2
	octave 4
	note G_, 8
	note G_, 6
	note Ds, 2
	note As, 8
	note G_, 6
	note As, 6
	note Gs, 2
	note G_, 2
	volume_envelope 11, 0
	note Ds, 8
	volume_envelope 11, 7
	note Ds, 8
	volume_envelope 12, 7
	note Ds, 6
	note As, 6
	note Gs, 2
	note G_, 2
	volume_envelope 11, 0
	note Ds, 8
	volume_envelope 11, 7
	note Ds, 8
	volume_envelope 12, 7
	octave 3
	note A_, 6
	octave 4
	note E_, 6
	note D_, 2
	note E_, 2
	note G_, 4
	note Fs, 4
	note E_, 4
	note D_, 4
	volume_envelope 11, 0
	note F_, 8
	volume_envelope 11, 7
	note F_, 8
	volume_envelope 11, 0
	note As, 8
	volume_envelope 11, 7
	note As, 8
	sound_call gbs_johtotrainerbattle_Ch2.sub2
	volume_envelope 12, 7
	note D_, 4
	octave 3
	note As, 2
	octave 4
	note D_, 2
	note F_, 2
	note E_, 2
	note D_, 2
	note F_, 2
	sound_loop 0, gbs_johtotrainerbattle_Ch2.mainloop

gbs_johtotrainerbattle_Ch2.sub1:
	octave 3
	note A_, 6
	note A_, 4
	note A_, 6
	note A_, 6
	volume_envelope 12, 7
	note As, 4
	sound_ret

gbs_johtotrainerbattle_Ch2.sub2:
	volume_envelope 12, 7
	octave 3
	note A_, 6
	octave 4
	note E_, 6
	note D_, 2
	note E_, 2
	note G_, 4
	note Fs, 4
	note E_, 4
	note D_, 4
	volume_envelope 11, 0
	note F_, 8
	volume_envelope 11, 7
	note F_, 8
	sound_ret

gbs_johtotrainerbattle_Ch2.sub3:
	octave 3
	note As, 2
	note Ds, 2
	octave 4
	note Ds, 2
	octave 3
	note Ds, 2
	sound_ret

gbs_johtotrainerbattle_Ch2.sub4:
	volume_envelope 12, 7
	octave 4
	note F_, 4
	volume_envelope 12, 4
	octave 3
	note As, 2
	octave 4
	note F_, 2
	note Gs, 2
	note G_, 2
	note F_, 2
	note Ds, 2
	note D_, 1
	note Ds, 1
	note D_, 1
	note Ds, 1
	note F_, 2
	sound_ret

gbs_johtotrainerbattle_Ch2.sub5:
	volume_envelope 12, 7
	octave 4
	note Ds, 6
	note As, 6
	note Gs, 2
	note G_, 2
	note Gs, 4
	note G_, 4
	note F_, 4
	note Ds, 4
	sound_ret

gbs_johtotrainerbattle_Ch3:
	gbs_switch 2
	note_type 12, 1, 9
	octave 4
	note E_, 1
	note Ds, 1
	note D_, 1
	note Cs, 1
	note D_, 1
	note Cs, 1
	note C_, 1
	octave 3
	note B_, 1
	octave 4
	note C_, 1
	octave 3
	note B_, 1
	note As, 1
	note A_, 1
	note As, 1
	note A_, 1
	note Gs, 1
	note G_, 1
	note Gs, 1
	note G_, 1
	note Fs, 1
	note F_, 1
	note Fs, 1
	note F_, 1
	note E_, 1
	note Ds, 1
	note E_, 2
	note As, 2
	note A_, 2
	note Gs, 2
gbs_johtotrainerbattle_Ch3.loop1:
	note A_, 2
	note E_, 2
	note Fs, 2
	note G_, 2
	note E_, 2
	note Fs, 2
	note G_, 2
	note E_, 2
	sound_loop 3, gbs_johtotrainerbattle_Ch3.loop1
	note A_, 2
	note E_, 2
	note Fs, 2
	note G_, 2
	note E_, 2
	note Fs, 2
	note G_, 2
	note Gs, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub1
	octave 4
	note C_, 2
	octave 3
	note G_, 2
	note A_, 2
	note As, 2
	octave 4
	note C_, 2
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub1
	octave 4
	note C_, 2
	octave 3
	note G_, 2
	note A_, 2
	note As, 2
	note G_, 2
	note A_, 2
	note As, 2
	note G_, 2
gbs_johtotrainerbattle_Ch3.mainloop:
	sound_call gbs_johtotrainerbattle_Ch3.sub2
	note E_, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub3
	sound_call gbs_johtotrainerbattle_Ch3.sub3
	sound_call gbs_johtotrainerbattle_Ch3.sub2
	note A_, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub3
	sound_call gbs_johtotrainerbattle_Ch3.sub3
	sound_call gbs_johtotrainerbattle_Ch3.sub4
	note E_, 2
	note A_, 2
	note E_, 2
	note A_, 2
	note E_, 2
	note D_, 2
	note E_, 2
	note F_, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub4
	note E_, 2
	octave 4
	note F_, 2
	note E_, 2
	note D_, 2
	octave 3
	note A_, 2
	note Gs, 2
	note A_, 2
	note As, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub5
	note D_, 2
	note A_, 2
	note D_, 2
	note A_, 2
	note D_, 2
	note A_, 2
	note G_, 2
	note A_, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub5
	note D_, 2
	octave 4
	note D_, 2
	note C_, 2
	octave 3
	note As, 2
	note A_, 2
	note G_, 2
	note A_, 2
	note As, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub6
	note C_, 2
	note G_, 2
	note C_, 2
	note G_, 2
	note C_, 2
	note G_, 2
	note F_, 2
	note G_, 2
	sound_call gbs_johtotrainerbattle_Ch3.sub6
	note C_, 2
	octave 4
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 2
	note F_, 2
	note Ds, 2
	note D_, 2
	note G_, 8
	note F_, 8
	note E_, 8
	note Ds, 8
gbs_johtotrainerbattle_Ch3.loop2:
	octave 3
	note Ds, 2
	note As, 2
	note Ds, 2
	note As, 2
	note Ds, 2
	note As, 2
	note A_, 2
	octave 4
	note C_, 2
	sound_loop 2, gbs_johtotrainerbattle_Ch3.loop2
	sound_call gbs_johtotrainerbattle_Ch3.sub6
	note C_, 2
	octave 4
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 2
	note F_, 2
	note Ds, 2
	note G_, 2
gbs_johtotrainerbattle_Ch3.loop3:
	note Cs, 2
	note Gs, 2
	sound_loop 7, gbs_johtotrainerbattle_Ch3.loop3
	note B_, 2
	note A_, 2
gbs_johtotrainerbattle_Ch3.loop4:
	note D_, 2
	note A_, 2
	sound_loop 5, gbs_johtotrainerbattle_Ch3.loop4
	note B_, 2
	note A_, 2
	note Gs, 2
	note Fs, 2
	note Gs, 2
	note A_, 2
gbs_johtotrainerbattle_Ch3.loop5:
	note As, 4
	note Ds, 4
	sound_loop 4, gbs_johtotrainerbattle_Ch3.loop5
gbs_johtotrainerbattle_Ch3.loop6:
	octave 4
	note G_, 4
	octave 3
	note As, 4
	sound_loop 4, gbs_johtotrainerbattle_Ch3.loop6
gbs_johtotrainerbattle_Ch3.loop7:
	sound_call gbs_johtotrainerbattle_Ch3.sub7
	note Ds, 2
	note F_, 8
	sound_call gbs_johtotrainerbattle_Ch3.sub7
	octave 4
	note C_, 2
	octave 3
	note As, 8
	sound_loop 2, gbs_johtotrainerbattle_Ch3.loop7
	octave 4
	note Cs, 8
	note C_, 8
	octave 3
	note As, 8
	note Gs, 8
	note F_, 8
	note G_, 8
	note Gs, 8
	note As, 8
	note F_, 8
	note G_, 8
	note Gs, 4
	note Ds, 2
	note Gs, 2
	octave 4
	note C_, 8
	note C_, 8
	note Ds, 8
	octave 3
	note As, 2
	note Gs, 2
	note G_, 2
	note F_, 2
	note Ds, 2
	note As, 2
	note Ds, 2
	note As, 2
	note Ds, 2
	note As, 2
	octave 4
	note Cs, 2
	octave 3
	note As, 2
	note Ds, 2
	note As, 2
	octave 4
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 2
	note Gs, 2
	note Ds, 2
	note As, 2
	note Ds, 2
	note As, 2
	note Ds, 2
	note As, 2
	octave 4
	note Cs, 2
	octave 3
	note As, 2
	note Ds, 2
	note As, 2
	octave 4
	note C_, 2
	note Cs, 2
	note Ds, 2
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
gbs_johtotrainerbattle_Ch3.loop8:
	note Ds, 2
	note As, 2
	sound_loop 8, gbs_johtotrainerbattle_Ch3.loop8
gbs_johtotrainerbattle_Ch3.loop9:
	note Cs, 2
	note Gs, 2
	sound_loop 6, gbs_johtotrainerbattle_Ch3.loop9
	note Cs, 2
	octave 4
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
gbs_johtotrainerbattle_Ch3.loop10:
	note Ds, 2
	note As, 2
	sound_loop 8, gbs_johtotrainerbattle_Ch3.loop10
gbs_johtotrainerbattle_Ch3.loop11:
	note Cs, 2
	note Gs, 2
	sound_loop 4, gbs_johtotrainerbattle_Ch3.loop11
	note Cs, 2
	octave 4
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
	note G_, 2
	note Gs, 2
	note As, 2
	octave 4
	note C_, 2
	octave 3
	note Ds, 8
	note Cs, 8
	note C_, 8
	octave 2
	note As, 8
	octave 3
	note As, 8
	note Gs, 8
	note G_, 8
	note F_, 8
	octave 4
	note Ds, 8
	note Ds, 8
	octave 3
	note As, 8
	note As, 8
	note G_, 8
	note G_, 8
	note Ds, 8
	note Ds, 4
	note As, 4
	note A_, 16
	octave 4
	note C_, 16
	octave 3
	note As, 16
	octave 4
	note D_, 16
	octave 3
	note A_, 16
	octave 4
	note C_, 16
	octave 3
	note As, 16
	octave 4
	note D_, 8
	rest 2
	octave 3
	note A_, 2
	note As, 2
	octave 4
	note D_, 2
	sound_loop 0, gbs_johtotrainerbattle_Ch3.mainloop

gbs_johtotrainerbattle_Ch3.sub1:
	octave 4
	note C_, 2
	octave 3
	note G_, 2
	note A_, 2
	note As, 2
	note G_, 2
	note A_, 2
	note As, 2
	note G_, 2
	sound_ret

gbs_johtotrainerbattle_Ch3.sub2:
	octave 3
	note E_, 2
	note A_, 2
	note E_, 2
	note A_, 2
	note E_, 2
	note Fs, 2
	note G_, 2
	note A_, 2
	note E_, 2
	note A_, 2
	note E_, 2
	note A_, 2
	note E_, 2
	note Fs, 2
	note G_, 2
	sound_ret

gbs_johtotrainerbattle_Ch3.sub3:
	octave 3
	note F_, 2
	note As, 2
	note F_, 2
	note As, 2
	note F_, 2
	note A_, 2
	note As, 2
	octave 4
	note D_, 2
	sound_ret

gbs_johtotrainerbattle_Ch3.sub4:
gbs_johtotrainerbattle_Ch3.sub4loop1:
	octave 3
	note E_, 2
	note A_, 2
	sound_loop 4, gbs_johtotrainerbattle_Ch3.sub4loop1
	sound_ret

gbs_johtotrainerbattle_Ch3.sub5:
gbs_johtotrainerbattle_Ch3.sub5loop1:
	note D_, 2
	note A_, 2
	sound_loop 4, gbs_johtotrainerbattle_Ch3.sub5loop1
	sound_ret

gbs_johtotrainerbattle_Ch3.sub6:
gbs_johtotrainerbattle_Ch3.sub6loop1:
	octave 3
	note C_, 2
	note G_, 2
	sound_loop 4, gbs_johtotrainerbattle_Ch3.sub6loop1
	sound_ret

gbs_johtotrainerbattle_Ch3.sub7:
	note As, 4
	note Ds, 2
	note As, 2
	octave 4
	note Cs, 2
	note C_, 2
	octave 3
	note As, 2
	note Gs, 2
	note G_, 1
	note Gs, 1
	note G_, 1
	note Gs, 1
	note As, 2
	sound_ret

	.align 4
	.global gbs_johtotrainerbattle_Header
gbs_johtotrainerbattle_Header:
	.byte 3	@ NumTrks
	.byte 0	@ NumBlks
	.byte 0	@ Priority
	.byte 0	@ Reverb

	.int voicegroup000

	.int gbs_johtotrainerbattle_Ch1
	.int gbs_johtotrainerbattle_Ch2
	.int gbs_johtotrainerbattle_Ch3
