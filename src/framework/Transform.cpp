#include "Transform.hpp"

namespace Framework {
	ImageFlip transform_to_imageflip(SpriteTransform transform) {
		switch (transform) {
		case SpriteTransform::FLIP_HORIZONTAL:	return ImageFlip::FLIP_HORIZONTAL;
		case SpriteTransform::FLIP_VERTICAL:	return ImageFlip::FLIP_VERTICAL;
		case SpriteTransform::SWAP_XY:			return ImageFlip::FLIP_BOTH;
		default:								return ImageFlip::FLIP_NONE;
		}
	}

	float transform_to_angle(SpriteTransform transform) {
		switch (transform) {
		case SpriteTransform::ROTATE_90_CW:		return 90.0f;
		case SpriteTransform::ROTATE_180_CW:	return 180.0f;
		case SpriteTransform::ROTATE_270_CW:	return 270.0f;
		default:								return 0.0f;
		}
	}
}