#include <libdragon.h>
#include <t3d/t3dmodel.h>
#include "setting.hpp"

void Setting::createSetting() {
   //  mapMatFP = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP));
   //
   //  t3d_mat4fp_from_srt_euler(mapMatFP, (float[3]){0.4f, 0.4f, 0.4f}, (float[3]){0, 0, 0}, (float[3]){0, 0, -10});
   //
   //  rspq_block_begin();
   //  	t3d_matrix_push(mapMatFP);
   //  	rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
   //  	t3d_model_draw(mapModel);
   //  	t3d_matrix_pop(1);
  	// dplMap = rspq_block_end();

	t3d_mat4_identity(&modelMat);
	modelMatFP = (T3DMat4FP*)malloc_uncached(sizeof(T3DMat4FP));

	vertices = (T3DVertPacked*)malloc_uncached(sizeof(T3DVertPacked) * 2);
	T3DVec3 startingNorm = (T3DVec3){{ 0, 0, 0}};
	uint16_t norm = t3d_vert_pack_normal(&startingNorm);
	vertices[0] = (T3DVertPacked) {
		.posA = {-140, 0, -140},
		.normA = norm,
		.posB = { 140, 0, -140},
		.normB = norm,
		.rgbaA = 0xFF0000'FF,
		.rgbaB = 0x00FF00'FF
	};
	vertices[1] = (T3DVertPacked) {
		.posA = { 140,  0, 140},
		.normA = norm,
		.posB = {-140,  0, 140},
		.normB = norm,
		.rgbaA = 0x0000FF'FF,
		.rgbaB = 0xFF00FF'FF
	};
	t3d_vec3_norm(&rotAxis);

	rspq_block_begin();
	t3d_matrix_push(modelMatFP);
	t3d_vert_load(vertices, 0, 4);
	t3d_matrix_pop(1);
	t3d_tri_draw(0, 1, 2);
	t3d_tri_draw(2, 3, 0);
	t3d_tri_sync();
	dplDraw = rspq_block_end();

	_physics.createGroundRigidBody();
};

void Setting::drawMap() {
	//rspq_block_run(dplMap);
	t3d_mat4_identity(&modelMat);
	t3d_mat4_rotate(&modelMat, &rotAxis, planeRotation);
	t3d_mat4_scale(&modelMat, 1.0f, 1.0f, 1.0f);
	t3d_mat4_to_fixed(modelMatFP, &modelMat);
	t3d_state_set_drawflags((T3DDrawFlags)(T3D_FLAG_SHADED | T3D_FLAG_DEPTH));

	rspq_block_run(dplDraw);
}
