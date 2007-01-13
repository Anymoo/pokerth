/***************************************************************************
 *   Copyright (C) 2006 by FThauer FHammer   *
 *   f.thauer@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "cardsvalue.h"

CardsValue::CardsValue()
{
}


CardsValue::~CardsValue()
{
}

int CardsValue::holeCardsClass(int one, int two) {

  if((one-1)%13<(two-1)%13) {
    int temp = one;
    one = two;
    two = temp;
  }


  if((one-1)%13 == (two-1)%13) {
    if((one-1)%13+2 > 10) return 10;
    else {
      switch((one-1)%13+2) {
        case 10: return 9;
        case 9: return 8;
        case 8: return 7;
        case 7: return 6;
        default: return 5;
      }
    }
  }
  switch((one-1)%13+2) {
  //Ass
    case 14: { 
      if((one-1)/13 == (two-1)/13) {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 10;
	  case 2: return 9;
	  case 3: return 9;
	  case 4: return 8;
	  default: return 7;
        }
      }
      else {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 9;
	  case 2: return 8;
	  case 3: return 7;
	  case 4: return 7;
	  default: return 4;
        }
      }
    } break;
    //K�nig
    case 13: { 
      if((one-1)/13 == (two-1)/13) {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 9;
	  case 2: return 8;
	  case 3: return 8;
	  case 4: return 6;
	  default: return 5;
        }
      }
      else {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 7;
	  case 2: return 6;
	  case 3: return 6;
	  default: return 4;
        }
      }
    } break;
    //Dame
    case 12: { 
      if((one-1)/13 == (two-1)/13) {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 8;
	  case 2: return 7;
	  case 3: return 6;
	  case 4: return 5;
	  default: return 4;
        }
      }
      else {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 6;
	  case 2: return 6;
	  case 3: return 4;
	  default: return 3;
        }
      }
    } break;
    //Bube
    case 11: { 
      if((one-1)/13 == (two-1)/13) {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 7;
	  case 2: return 6;
	  case 3: return 5;
	  case 4: return 4;
	  default: return 3;
        }
      }
      else {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 6;
	  case 2: return 5;
	  case 3: return 4;
	  default: return 2;
        }
      }
    } break;
    //10
    case 10: { 
      if((one-1)/13 == (two-1)/13) {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 6;
	  case 2: return 5;
	  default: return 2;
        }
      }
      else {
        switch((one-1)%13-(two-1)%13) {
          case 1: return 5;
	  case 2: return 4;
	  default: return 1;
        }
      }
    } break;
    //Rest
    default: {
      if((one-1)%13 - (two-1)%13 <= 2) {
        if((one-1)/13 == (two-1)/13) return 5;
        else return 3;
      }
      else {
        if((one-1)%13 - (two-1)%13 == 3) return 2;
        else return 1;
      }
    }
 }


}

int CardsValue::cardsValue(int *cards) {

int array[7][2];
	int j1, j2, j3, j4, j5, k1, k2, ktemp[2];

	// Kartenwerte umwandeln (z.B. [ 11 (Karo K�nig) -> 0 11 ] oder [ 31 (Pik 7) -> 2 5 ] )
	for(j1=0; j1<7; j1++) {
		array[j1][0] = cards[j1]/13;
		array[j1][1] = cards[j1]%13;
	}

	// Karten nach Farben sortieren: Kreuz - Pik - Herz - Karo
	for(k1=0; k1<7; k1++) {
		for(k2=k1+1; k2<7; k2++) {
			if(array[k1][0]<array[k2][0]) {
				ktemp[0] = array[k1][0];
				ktemp[1] = array[k1][1];
				array[k1][0] = array[k2][0];
				array[k1][1] = array[k2][1];
				array[k2][0] = ktemp[0];
				array[k2][1] = ktemp[1];
			}
		}
	}

	// Karten innerhalb der Farben nach der Gr��e sortieren: Ass - K�nig - Dame - ... - 4 - 3 - 2
	for(k1=0; k1<7; k1++) {
		for(k2=k1+1; k2<7; k2++) {
			if(array[k1][0]==array[k2][0] && array[k1][1]<array[k2][1]) {
				ktemp[0] = array[k1][0];
				ktemp[1] = array[k1][1];
				array[k1][0] = array[k2][0];
				array[k1][1] = array[k2][1];
				array[k2][0] = ktemp[0];
				array[k2][1] = ktemp[1];
			}
		}
	}

	// Karten auf Bl�tter testen. Klasseneinteilung absteigend: 9 - Royal Flush, 8 - Straight Flush, ... 2 - Zwei Paare, 1 - Ein Paar, 0 - Nischt

	// auf Royal Flush (Klasse 9) und Straight Flush (Klasse 8) testen
	for(j1=0; j1<3; j1++) {
		// 5 Karten gleiche Farbe ?
		if(array[j1][0] == array[j1+1][0] && array[j1][0] == array[j1+2][0] && array[j1][0] == array[j1+3][0] && array[j1][0] == array[j1+4][0]) {
			// zus�tzlich in Stra�enform ?
			if(array[j1][1]-1 == array[j1+1][1] && array[j1+1][1]-1 == array[j1+2][1] && array[j1+2][1]-1 == array[j1+3][1] && array[j1+3][1]-1 == array[j1+4][1]) {
				// mit Ass an der Spitze ?
				if(array[j1][1] == 12) {
					// Royal Flush (9*100000000)
					return 900000000;
				}
				// sonst nur Straight Flush (8*100000000 + (h�chste Straight-Karte)*1000000)
				else return 800000000+array[j1][1]*1000000;
			}
			else {
			// Straight Flush Ausnahme: 5-4-3-2-A
				for(j2=j1+1; j2<7; j2++) {
					if(array[j1][1]-9==array[j2][1] && array[j2][1]-1==array[j2+1][1] && array[j2+1][1]-1==array[j2+2][1] && array[j2+2][1]-1==array[j2+3][1] && array[j1][0]==array[j2+2][0] && array[j1][0]==array[j2+3][0]) {
						// Straight Flush mit 5 als h�hste Karte -> 8*100000000+3*1000000
						return 800000000+3*1000000;
					}
				}
			}
		}
	}

	// auf Flush (Klasse 5) testen
	for(j1=0; j1<3; j1++) {
		if(array[j1][0] == array[j1+1][0] && array[j1][0] == array[j1+2][0] && array[j1][0] == array[j1+3][0] && array[j1][0] == array[j1+4][0]) {
			// Flush -> 5*10000000 + h�hste Flush Karten mit absteigender Wertung
			return 500000000+array[j1][1]*1000000+array[j1+1][1]*10000+array[j1+2][1]*100+array[j1+3][1]*10+array[j1+4][1];
		}
	}



	// Karten f�r den Vierling-, Full-House-, Drilling- und Paartest umsortieren
	for(k1=0; k1<7; k1++) {
		for(k2=k1+1; k2<7; k2++) {
			if(array[k1][1]<array[k2][1]) {
				ktemp[0] = array[k1][0];
				ktemp[1] = array[k1][1];
				array[k1][0] = array[k2][0];
				array[k1][1] = array[k2][1];
				array[k2][0] = ktemp[0];
				array[k2][1] = ktemp[1];
			}
		}
	}

	// auf Vierling (Klasse 7) testen
	for(j1=0; j1<4; j1++) {
		if(array[j1][1] == array[j1+1][1] && array[j1][1] == array[j1+2][1] && array[j1][1] == array[j1+3][1]) {
			// Position des Kickers ermitteln und der Blattwertung als dritte Gewichtung hinzuaddieren
			if(j1==0) return 700000000+array[j1][1]*1000000+array[j1+4][1]*10000;
			else return 700000000+array[j1][1]*1000000+array[0][1]*10000;
		}
	}

	// Hilfsvariablen fr die Full-House-Paar- und -Drilling-Zuordnung
	int drei, zwei;

	// auf Straight (Klasse 4) und Full House (Klasse 6) testen
	for(j1=0; j1<7; j1++) {
		for(j2=j1+1; j2<7; j2++) {
			for(j3=j2+1; j3<7; j3++) {
				for(j4=j3+1; j4<7; j4++) {
					for(j5=j4+1; j5<7; j5++) {
						// Straight
						if((array[j1][1]-1 == array[j2][1] || array[j1][1]-9 == array[j2][1] ) && array[j2][1]-1 == array[j3][1] && array[j3][1]-1 == array[j4][1] && array[j4][1]-1 == array[j5][1]) {
							// h�hste Karte der Straight ermitteln
							if(array[j1][1]-9 == array[j2][1]) return 400000000+array[j2][1]*1000000;
							else return 400000000+array[j1][1]*1000000;
						}
						// Full House
						if((array[j1][1] == array[j2][1] && array[j1][1] == array[j3][1] && array[j4][1] == array[j5][1]) || (array[j3][1] == array[j4][1] && array[j3][1] == array[j5][1] && array[j1][1] == array[j2][1])) {
							// Paar und Drilling des Full House ermitteln ermitteln
							if(array[j3][1]==array[j1][1]) { drei = array[j1][1]; zwei = array[j4][1]; }
							else { drei = array[4][1]; zwei = array[j1][1]; }
							return 600000000+drei*1000000+zwei*10000;
						}
					}
				}
			}
		}
	}

	// auf Drilling (Klasse 3) testen
	for(j1=0; j1<5; j1++) {
		if(array[j1][1] == array[j1+1][1] && array[j1][1] == array[j1+2][1]) {
			// Kicker ermitteln
			if(j1==0) return 300000000+array[j1][1]*1000000+array[j1+3][1]*10000+array[j1+4][1]*100;
			else {
				if(j1==1) return 300000000+array[j1][1]*1000000+array[j1-1][1]*10000+array[j1+3][1]*100;
				else return 300000000+array[j1][1]*1000000+array[0][1]*10000+array[1][1]*100;
			}
		}
	}

	// auf Zwei Paare (Klasse 2) testen
	for(j1=0; j1<4; j1++) {
		for(j2=j1+2; j2<6; j2++) {
			if(array[j1][1] == array[j1+1][1] && array[j2][1] == array[j2+1][1]) {
				// Kicker ermitteln
				if(j1==0) {
					if(j2==2) return 200000000+array[j1][1]*1000000+array[j2][1]*10000+array[j2+2][1]*100;
					else return 200000000+array[j1][1]*1000000+array[j2][1]*10000+array[j1+2][1]*100;
				}
				else return 200000000+array[j1][1]*1000000+array[j2][1]*10000+array[0][1]*100;
			}
		}
	}

	// auf Paar (Klasse 1) testen
	for(j1=0; j1<6; j1++) {
		if(array[j1][1] == array[j1+1][1]) {
			// Kicker ermitteln
			if(j1==0) return 100000000+array[j1][1]*1000000+array[j1+2][1]*10000+array[j1+3][1]*100+array[j1+4][1];
			if(j1==1) return 100000000+array[j1][1]*1000000+array[j1-1][1]*10000+array[j1+2][1]*100+array[j1+3][1];
			if(j1==2) return 100000000+array[j1][1]*1000000+array[j1-2][1]*10000+array[j1-1][1]*100+array[j1+2][1];
			else return 100000000+array[j1][1]*1000000+array[0][1]*10000+array[1][1]*100+array[2][1];
		}
	}

	// Highest Card (Klasse 0) + Kicker
	return array[0][1]*1000000+array[1][1]*10000+array[2][1]*100+array[3][1]*10+array[4][1];
} 

