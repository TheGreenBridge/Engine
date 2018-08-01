//
//#include <graphics\pbr\PBRMaterial.h>
//
//namespace engine {
//	namespace graphics {
//		PBRMaterial::PBRMaterial(const Texture &albedo,
//			const Texture &metallic,
//			const Texture &roughness,
//			const Shader &shader): 
//			m_Albedo(albedo), m_Metallic(metallic), m_Roughness(roughness), m_Shader(shader)
//		{ }
//
//		U32 PBRMaterial::getAlbedo() const
//		{
//			return m_Albedo.getID();
//		}
//
//		U32 PBRMaterial::getNormal() const
//		{
//			return m_Normal.getID();
//		}
//
//		U32 PBRMaterial::getMetallic() const
//		{
//			return m_Metallic.getID();
//		}
//
//		U32 PBRMaterial::getRoughness() const
//		{
//			return m_Roughness.getID();
//		}
//		const Shader & PBRMaterial::getShader() const
//		{
//			return m_Shader;
//		}
//	}
//}
