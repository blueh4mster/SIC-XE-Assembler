#include "../headers/Pass2.h"

string errorMessages;
void runPass2(ofstream* opFile, vector<cSect>* cSects, bool& successfullPass2, string& baseOp) {

	errorMessages = "";
	writeBorder_Pass2(opFile);
	writeHeader_Pass2(opFile);
	vector<vector<string> > objectCodes;
	bool success = true;
	int starting = cSects->at(0).locpl.at(0).loc;
	cSect cc = cSects->at(cSects->size() - 1);
	int ending = cc.locpl.at(cc.locpl.size() - 1).loc;
	for (unsigned int i = 0; i < cSects->size(); i++) {
		vector<string> ii;
		objectCodes.push_back(ii);
		vector<locatedParsedLine> v = cSects->at(i).locpl;
		for (unsigned j = 0; j < v.size() - 1; j++) {
			opCode x;
			string objectCode = "";
			try {
				// int baseReg = -1;
				// if (baseOp.compare("") !=0){
				// 	baseReg = evaluateBaseOperand(baseOp, &(cSects->at(i)));
				// }
				x = generateOpCode(v[j].p, v[j + 1].loc, &(cSects->at(i)),baseOp);
				objectCode = calcOpCode(x);
				if (objectCode.length() == 5){
					objectCode = "0"+objectCode;
				} else if (objectCode.length() == 7){
					objectCode = "0"+objectCode;
				}
				// cout<<objectCode<<endl;
			} catch (string* err) {
				errorMessages += "\n";
				errorMessages += *err;
				success = false;
				delete err;
			} catch (string& err) {
				errorMessages += "\n";
				errorMessages += err;
				success = false;
			}

			string operands = v[j].p.operand1;
			if (v[j].p.operand2 != ""){
				operands = operands +","+v[j].p.operand2;
			}
			string line = constructLine_Pass2(v[j].loc, v[j].p.lable,
					v[j].p.opcode, operands, x.flags, objectCode);

			objectCodes[i].push_back(objectCode);
			writeLine(opFile, line);

			if (errorMessages.compare("") != 0) {
				writeError(opFile, errorMessages);
				errorMessages = "";
			}
		}
	}
	successfullPass2 = success;

	if (!success)
		return;

	opFile->close();

	string out2 = "../output/objectFile.txt";
	deleteFile(out2.c_str());
	opFile->open(out2.c_str(), std::ios::app);

	for (unsigned int i = 0; i < cSects->size(); i++) {
		writeHeaderRecord(opFile, cSects->at(i).name, starting, ending - starting);
		writeDefineRecord(opFile, &(cSects->at(i).extDef),
				&(cSects->at(i).symTab));
		writeReferRecord(opFile, &(cSects->at(i).extRef));
		writeTextRecords(opFile, &(objectCodes[i]), &(cSects->at(i).locpl));
		writeModRecords(opFile, &(cSects->at(i).mods));
		writeEndRecord(opFile, starting);
		writeBorder_Pass2(opFile);
	}

	return;
}
