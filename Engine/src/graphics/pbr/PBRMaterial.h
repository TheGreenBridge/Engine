//#pragma once
//
//#include <graphics\api\Texture.h>
//#include <graphics\api\Shader.h>
//#include <math\Vec3.h>
//
//namespace engine {
//	namespace graphics {
//
//		class PBRMaterial {
//		private:
//			Texture* m_Albedo;
//			Texture* m_Normal;
//			Texture* m_Metallic;
//			//Texture* m_Roughness;
//			Texture* m_AO;
//			Shader* m_Shader;
//		public:
//			PBRMaterial(const Texture &albedo, 
//				const Texture &metallic, 
//				const Texture &roughness,
//				const Shader &shader);
//
//			float roughness, metallic, ao;
//			Vec3 albedo;
//			U32 getAlbedo() const;
//			U32 getNormal() const;
//			U32 getMetallic() const;
//			U32 getRoughness() const;
//			const Shader &getShader() const;
//		};
//		
//	}
//}