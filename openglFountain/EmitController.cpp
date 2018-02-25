#include "EmitController.h"


EmitController::EmitController()
{
}


EmitController::~EmitController()
{
}

void EmitController::addRotateEmitter(std::string group, Emitter *emitter, float factor) {
	//addEmitter(&rotateMap, group, emitter, factor);
	EmitterUnit unit;
	unit.emitter = emitter;
	unit.factor = factor;
	auto it = rotateMap.find(group);
	if (it == rotateMap.end()) {
		std::vector<EmitterUnit> emitters;
		emitters.push_back(unit);
		rotateMap.insert(std::pair<std::string, std::vector<EmitterUnit>>(group, emitters));
	}
	else {
		std::vector<EmitterUnit> &emitters = it->second;
		emitters.push_back(unit);
	}
}

void EmitController::addShiftEmitter(std::string group, Emitter *emitter, float factor) {
	//addEmitter(&shiftMap, group, emitter, factor);
	EmitterUnit unit;
	unit.emitter = emitter;
	unit.factor = factor;
	auto it = shiftMap.find(group);
	if (it == shiftMap.end()) {
		std::vector<EmitterUnit> emitters;
		emitters.push_back(unit);
		shiftMap.insert(std::pair<std::string, std::vector<EmitterUnit>>(group, emitters));
	}
	else {
		std::vector<EmitterUnit> &emitters = it->second;
		emitters.push_back(unit);
	}
}

void EmitController::addWaveEmitter(std::string group, Emitter *emitter, float factor) {
	//addEmitter(&waveMap, group, emitter, factor);
	EmitterUnit unit;
	unit.emitter = emitter;
	unit.factor = factor;
	auto it = waveMap.find(group);
	if (it == waveMap.end()) {
		std::vector<EmitterUnit> emitters;
		emitters.push_back(unit);
		waveMap.insert(std::pair<std::string, std::vector<EmitterUnit>>(group, emitters));
	}
	else {
		std::vector<EmitterUnit> &emitters = it->second;
		emitters.push_back(unit);
	}
}

void EmitController::addBlossomEmitter(std::string group, Emitter *emitter, float factor) {
	//addEmitter(&blossomMap, group, emitter, factor);
	EmitterUnit unit;
	unit.emitter = emitter;
	unit.factor = factor;
	auto it = blossomMap.find(group);
	if (it == blossomMap.end()) {
		std::vector<EmitterUnit> emitters;
		emitters.push_back(unit);
		blossomMap.insert(std::pair<std::string, std::vector<EmitterUnit>>(group, emitters));
	}
	else {
		std::vector<EmitterUnit> &emitters = it->second;
		emitters.push_back(unit);
	}
}

void EmitController::addFloodEmitter(std::string group, Emitter *emitter, float factor) {
	//addEmitter(&floodMap, group, emitter, factor);
	EmitterUnit unit;
	unit.emitter = emitter;
	unit.factor = factor;
	auto it = floodMap.find(group);
	if (it == floodMap.end()) {
		std::vector<EmitterUnit> emitters;
		emitters.push_back(unit);
		floodMap.insert(std::pair<std::string, std::vector<EmitterUnit>>(group, emitters));
	}
	else {
		std::vector<EmitterUnit> &emitters = it->second;
		emitters.push_back(unit);
	}
}

void EmitController::rotate(std::string group, float delta) {
	auto it = rotateMap.find(group);
	if (it == rotateMap.end()) return;
	std::vector<EmitterUnit> &emitters = it->second;
	for (auto i = emitters.begin(); i != emitters.end(); i++) {
		i->emitter->renewTheta(delta * i->factor);
	}
}

void EmitController::shift(std::string group, float delta) {
	auto it = shiftMap.find(group);
	if (it == shiftMap.end()) return;
	std::vector<EmitterUnit> &emitters = it->second;
	for (auto i = emitters.begin(); i != emitters.end(); i++) {
		i->emitter->renewSpeed(delta * i->factor);
	}
}

void EmitController::wave(std::string group, float delta) {
	auto it = waveMap.find(group);
	if (it == waveMap.end()) return;
	std::vector<EmitterUnit> &emitters = it->second;
	for (auto i = emitters.begin(); i != emitters.end(); i++) {
		i->emitter->renewGama(delta * i->factor);
	}
}
void EmitController::blossom(std::string group, float delta) {
	auto it = blossomMap.find(group);
	if (it == blossomMap.end()) return;
	std::vector<EmitterUnit> &emitters = it->second;
	for (auto i = emitters.begin(); i != emitters.end(); i++) {
		i->emitter->renewDeltaAngle(delta * i->factor);
	}
}

void EmitController::flood(std::string group, float delta) {
	auto it = floodMap.find(group);
	if (it == floodMap.end()) return;
	std::vector<EmitterUnit> &emitters = it->second;
	for (auto i = emitters.begin(); i != emitters.end(); i++) {
		i->emitter->renewEmitNum(int(delta * i->factor));
	}
}

void EmitController::resetSpeed(std::string group) {
	auto it = shiftMap.find(group);
	if (it == shiftMap.end()) return;
	std::vector<EmitterUnit> &emitters = it->second;
	for (auto i = emitters.begin(); i != emitters.end(); i++) {
		i->emitter->resetSpeed();
	}
}

void EmitController::clear() {
	rotateMap.clear();
	shiftMap.clear();
	waveMap.clear();
	blossomMap.clear();
	floodMap.clear();
}