/* Oracle Redo OpCode: 11.4
   Copyright (C) 2018-2019 Adam Leszczynski.

This file is part of Open Log Replicator.

Open Log Replicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

Open Log Replicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with Open Log Replicator; see the file LICENSE.txt  If not see
<http://www.gnu.org/licenses/>.  */

#include <iostream>
#include <iomanip>
#include "OpCode0B04.h"
#include "OracleEnvironment.h"
#include "RedoLogRecord.h"

using namespace std;

namespace OpenLogReplicatorOracle {

	OpCode0B04::OpCode0B04(OracleEnvironment *oracleEnvironment, RedoLogRecord *redoLogRecord) :
			OpCode(oracleEnvironment, redoLogRecord) {

		uint32_t fieldPosTmp = redoLogRecord->fieldPos;
		for (uint32_t i = 1; i <= redoLogRecord->fieldNum; ++i) {
			if (i == 1) {
				ktbRedo(fieldPosTmp, redoLogRecord->fieldLengths[i]);
			} else if (i == 2) {
				kdoOpCode(fieldPosTmp, redoLogRecord->fieldLengths[i]);
			}

			fieldPosTmp += (redoLogRecord->fieldLengths[i] + 3) & 0xFFFC;
		}
	}

	OpCode0B04::~OpCode0B04() {
	}


	uint16_t OpCode0B04::getOpCode(void) {
		return 0x0B04;
	}

	string OpCode0B04::getName() {
		return "REDO LKR   ";
	}

	//lock row
	void OpCode0B04::process() {
		dump();
	}
}