//
//  fpu_softroots.c
//  plasmvm
//
//  Created by Noah Wooten on 3/2/22.
//

#include "../fpu.h"

x64 fpu_primeroots[4][16] = {
	{
		1.4142135623730951, // 2
		1.7320508075688772, // 3
		2.2360679774997900, // 5
		2.6457513110645907, // 7
		3.3166247903554000, // 11
		3.6055512754639890, // 13
		4.1231056256176610, // 17
		4.3588989435406740, // 19
		4.7958315233127190, // 23
		5.3851648071345040, // 29
		5.5677643628300215, // 31
		6.0827625302982190, // 37
		6.4031242374328485, // 41
		6.5574385243020000, // 43
		6.8556546004010440, // 47
		7.2801098892805180, // 53
	}, // Square Roots
	{
		1.2599210498948732, // 2
		1.4422495703074083, // 3
		1.7099759466766968, // 5
		1.9129311827723890, // 7
		2.2239800905693152, // 11
		2.3513346877207573, // 13
		2.5712815906582350, // 17
		2.6684016487219450, // 19
		2.8438669798515654, // 23
		3.0723168256858470, // 29
		3.1413806523913927, // 31
		3.3322218516459530, // 37
		3.4482172403827303, // 41
		3.5033980603867240, // 43
		3.6088260801386944, // 47
		3.7562857542210720, // 53
	}, // Cubic Roots
	{
		1.1892071150027210, // 2
		1.3160740129524924, // 3
		1.4953487812212205, // 5
		1.6265765616977856, // 7
		1.8211602868378718, // 11
		1.8988289221159418, // 13
		2.0305431848689306, // 17
		2.0877976299298440, // 19
		2.1899387030948420, // 23
		2.3205957871060840, // 29
		2.3596110617705670, // 31
		2.4663257145596607, // 37
		2.5304395344352430, // 41
		2.5607496020310148, // 43
		2.6183304986958853, // 47
		2.6981678764080854, // 53
	}, // Quadratic Roots
	{
		1.1486983549970350, // 2
		1.2457309396155174, // 3
		1.3797296614612150, // 5
		1.4757731615945522, // 7
		1.6153942662021780, // 11
		1.6702776523348104, // 13
		1.7623403478323170, // 17
		1.8019831273171423, // 19
		1.8721712305548575, // 23
		1.9610090574545480, // 29
		1.9873407546644581, // 31
		2.0589241364785170, // 37
		2.1016324782757847, // 41
		2.1217474608418980, // 43
		2.1598300117644660, // 47
		2.2123568222761167, // 53
	}, // Quintic Roots
};

u32 fpu_primes[16] = {
	2,
	3,
	5,
	7,
	11,
	13,
	17,
	19,
	23,
	29,
	31,
	37,
	41,
	43,
	47,
	53
};

x64 fpui_getprimeroot(int Root, int Prime) {
	int it = 0;
	switch (Prime) {
		case 2:
			it = 0;
			break;
		case 3:
			it = 1;
			break;
		case 5:
			it = 2;
			break;
		case 7:
			it = 3;
			break;
		case 11:
			it = 4;
			break;
		case 13:
			it = 5;
			break;
		case 17:
			it = 6;
			break;
		case 19:
			it = 7;
			break;
		case 23:
			it = 8;
			break;
		case 29:
			it = 9;
			break;
		case 31:
			it = 10;
			break;
		case 37:
			it = 11;
			break;
		case 41:
			it = 12;
			break;
		case 43:
			it = 13;
			break;
		case 47:
			it = 14;
			break;
		case 53:
			it = 15;
			break;
		default:
			it = 16;
			break;
	}
	if (it == 16)
		return -1;
	return fpu_primeroots[Root][it];
}

x64 intexp(x64 number, x64 power) {
	x64 Return = 1;
	for (int i = 0; i < power; i++) {
		Return *= number;
	}
	return Return;
}

x64 fpui_try(x64 guess, x64 number, x64 root) {
	x64 Return;
	Return = (((number) / (intexp(guess, (root - 1)))) + (guess * (root - 1))) / (root);
	return Return;
}

x64 fpui_tryi(x64 guess, x64 number, x64 root, int count) {
	if (count == 0)
		return guess;
	else
		return fpui_tryi(fpui_try(guess, number, root), number, root, count - 1);
}

x64 fpui_rooti(x64 Number, int Root) {
	x64 FirstGuess = 1;
	x64 Primal = 1;
	int Multiplier = 1;
	if (Root > 5)
		FirstGuess = fpui_getprimeroot(4, Number);
	else
		FirstGuess = fpui_getprimeroot(Root - 2, Number);
	if (FirstGuess == -1) {
		int PassedRoot = 1;
		FirstGuess = Number;
		if (Root > 5)
			PassedRoot = 3;
		else
			PassedRoot = Root - 2;
		for (int i = 0; i < 16; i++) {
			if (fpud_mod(FirstGuess, fpu_primes[i]) == 0) {
				while (1) {
					if (fpud_mod(FirstGuess, fpu_primes[i]) != 0) {
						break;
					} else {
						Primal *= fpui_getprimeroot(PassedRoot, (int)fpu_primes[i]);
						FirstGuess /= fpu_primes[i];
					}
				}
			}
		}
	}
	FirstGuess = Primal;
	x64 Return = fpui_tryi(FirstGuess, Number, Root, 5);
	Return *= Multiplier;
	x64 Checker = 1.0;
	for (int i = 0; i < Root; i++) {
		Checker *= Return;
	}
	int Precision = 4;
	while (fpud_abs(Checker - Number) > fpud_log2(Number)) {
		Return = fpui_tryi(Return, Number, Root, Precision);
		x64 Checker = 1.0;
		for (int i = 0; i < Root; i++) {
			Checker *= Return;
		}
		Precision++;
	}
	return fpud_abs(Return);
}
