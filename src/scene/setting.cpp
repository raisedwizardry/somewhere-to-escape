#include <libdragon.h>
#include <t3d/t3dmodel.h>
#include "setting.hpp"

void Setting::createSetting() {
    mapMatFP = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP));

    t3d_mat4fp_from_srt_euler(mapMatFP, (float[3]){0.05f, 0.05f, 0.05f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    rspq_block_begin();
    	t3d_matrix_push(mapMatFP);
    	t3d_model_draw(mapModel);
    	t3d_matrix_pop(1);
  	dplMap = rspq_block_end();

	_physics.createGroundRigidBody();
};

void Setting::drawMap() {
	rspq_block_run(dplMap);
}
