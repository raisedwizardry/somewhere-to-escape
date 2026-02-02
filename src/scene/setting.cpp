#include <libdragon.h>
#include <t3d/t3dmodel.h>
#include "setting.hpp"

void Setting::createSetting() {
	_physics.createGroundRigidBody();

	rspq_block_begin();
		t3d_matrix_push(greenMap.modelMat);

		t3d_model_draw(greenModel);
		t3d_matrix_pop(1);
	greenMap.dpl = rspq_block_end();

	rspq_block_begin();
		t3d_matrix_push(forestMap.modelMat);

		t3d_model_draw(forestModel);
		t3d_matrix_pop(1);
	forestMap.dpl = rspq_block_end();

	rspq_block_begin();
		t3d_matrix_push(juriWorldMap.modelMat);

		t3d_model_draw(juriWorldModel);
		t3d_matrix_pop(1);
	juriWorldMap.dpl = rspq_block_end();

	t3d_mat4fp_from_srt_euler(greenMap.modelMat, greenMap.scale, greenMap.rotation, greenMap.position);
	t3d_mat4fp_from_srt_euler(forestMap.modelMat, forestMap.scale, forestMap.rotation, forestMap.position);
	t3d_mat4fp_from_srt_euler(juriWorldMap.modelMat, juriWorldMap.scale, juriWorldMap.rotation, juriWorldMap.position);

};

void Setting::drawMap(GameState gameState) {
	if (gameState == LEVEL_1) {
		rspq_block_run(greenMap.dpl);
	}
	else if (gameState == LEVEL_2) {
		rspq_block_run(forestMap.dpl);
	}
	else if (gameState == LEVEL_3) {
		rspq_block_run(juriWorldMap.dpl);
	}
}
