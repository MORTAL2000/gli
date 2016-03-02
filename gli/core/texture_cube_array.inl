namespace gli
{
	inline texture_cube_array::texture_cube_array()
	{}

	inline texture_cube_array::texture_cube_array(format_type Format, extent_type const& Extent, size_type Layers, swizzles_type const& Swizzles)
		: texture(TARGET_CUBE_ARRAY, Format, texture::extent_type(Extent, 1), Layers, 6, gli::levels(Extent), Swizzles)
	{}

	inline texture_cube_array::texture_cube_array(format_type Format, extent_type const& Extent, size_type Layers, size_type Levels, swizzles_type const& Swizzles)
		: texture(TARGET_CUBE_ARRAY, Format, texture::extent_type(Extent, 1), Layers, 6, Levels, Swizzles)
	{}

	inline texture_cube_array::texture_cube_array(texture const & Texture)
		: texture(Texture, gli::TARGET_CUBE_ARRAY, Texture.format())
	{}

	inline texture_cube_array::texture_cube_array
	(
		texture const & Texture,
		format_type Format,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel,
		swizzles_type const& Swizzles
	)
		: texture(
			Texture, gli::TARGET_CUBE_ARRAY,
			Format,
			BaseLayer, MaxLayer,
			BaseFace, MaxFace,
			BaseLevel, MaxLevel,
			Swizzles)
	{}

	inline texture_cube_array::texture_cube_array
	(
		texture_cube_array const & Texture,
		size_type BaseLayer, size_type MaxLayer,
		size_type BaseFace, size_type MaxFace,
		size_type BaseLevel, size_type MaxLevel
	)
		: texture(
			Texture, gli::TARGET_CUBE_ARRAY, Texture.format(),
			Texture.base_layer() + BaseLayer, Texture.base_layer() + MaxLayer,
			Texture.base_face() + BaseFace, Texture.base_face() + MaxFace,
			Texture.base_level() + BaseLevel, Texture.base_level() + MaxLevel)
	{}

	inline texture_cube texture_cube_array::operator[](size_type Layer) const
	{
		GLI_ASSERT(Layer < this->layers());

		return texture_cube(
			*this, this->format(),
			this->base_layer() + Layer, this->base_layer() + Layer,
			this->base_face(), this->max_face(),
			this->base_level(), this->max_level());
	}

	inline texture_cube_array::extent_type texture_cube_array::extent(size_type Level) const
	{
		return extent_type(this->texture::extent(Level));
	}

	template <typename gen_type>
	inline gen_type texture_cube_array::load(extent_type const& TexelCoord, size_type Layer,  size_type Face, size_type Level) const
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(!is_compressed(this->format()));
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));

		size_type const ImageOffset = this->Storage->image_offset(TexelCoord, this->extent(Level));
		GLI_ASSERT(ImageOffset < this->size<gen_type>(Level));

		return *(this->data<gen_type>(Layer, Face, Level) + ImageOffset);
	}

	template <typename gen_type>
	inline void texture_cube_array::store(extent_type const& TexelCoord, size_type Layer,  size_type Face, size_type Level, gen_type const& Texel)
	{
		GLI_ASSERT(!this->empty());
		GLI_ASSERT(!is_compressed(this->format()));
		GLI_ASSERT(block_size(this->format()) == sizeof(gen_type));
		GLI_ASSERT(glm::all(glm::lessThan(TexelCoord, this->extent(Level))));

		size_type const ImageOffset = this->Storage->image_offset(TexelCoord, this->extent(Level));
		GLI_ASSERT(ImageOffset < this->size<gen_type>(Level));

		*(this->data<gen_type>(Layer, Face, Level) + ImageOffset) = Texel;
	}
}//namespace gli
