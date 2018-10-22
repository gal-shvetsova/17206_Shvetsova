#pragma once
#ifndef  TRIT_H
#define TRIT_H

enum trit { Unknown = 0, True, False };

trit operator&(const trit&, const trit&);
trit operator|(const trit&, const trit&);
trit operator~(const trit&);

#endif // ! TRIT_H