//
//  MaterialFactory.cpp
//  Chilli Source
//  Created by Scott Downie on 5/08/2013.
//
//  The MIT License (MIT)
//
//  Copyright (c) 2013 Tag Games Limited
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#include <ChilliSource/Rendering/Material/MaterialFactory.h>

#include <ChilliSource/Core/Base/Application.h>
#include <ChilliSource/Core/Resource/ResourcePool.h>
#include <ChilliSource/Rendering/Base/CullFace.h>
#include <ChilliSource/Rendering/Material/Material.h>
#include <ChilliSource/Rendering/Shader/Shader.h>

namespace ChilliSource
{
    CS_DEFINE_NAMEDTYPE(MaterialFactory);
    
    //-------------------------------------------------------
    //-------------------------------------------------------
    MaterialFactoryUPtr MaterialFactory::Create()
    {
        return MaterialFactoryUPtr(new MaterialFactory());
    }
    //---------------------------------------------------
    //---------------------------------------------------
    bool MaterialFactory::IsA(InterfaceIDType in_interfaceId) const
    {
        return in_interfaceId == MaterialFactory::InterfaceID;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateCustom(const std::string& in_uniqueId) const
    {
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        return resourcePool->CreateResource<Material>(in_uniqueId);
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateGUI(const std::string& in_uniqueId) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_unlit);
        material->SetTransparencyEnabled(true);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        material->SetDepthTestEnabled(false);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateSprite(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_unlit);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(false);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStatic(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_unlit);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStaticAmbient(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_unlit);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStaticBlinn(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_blinn);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStaticBlinnShadowed(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticAmbient.csshader"));
//        material->SetShader(ShaderPass::k_directional, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticBlinnShadowedDirectional.csshader"));
//        material->SetShader(ShaderPass::k_point, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticBlinnPoint.csshader"));
//        material->AddTexture(in_texture);
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStaticBlinnPerVertex(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticAmbient.csshader"));
//        material->SetShader(ShaderPass::k_directional, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticBlinnPerVertexDirectional.csshader"));
//        material->SetShader(ShaderPass::k_point, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticBlinnPerVertexPoint.csshader"));
//        material->AddTexture(in_texture);
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStaticBlinnPerVertexShadowed(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticAmbient.csshader"));
//        material->SetShader(ShaderPass::k_directional, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticBlinnPerVertexShadowedDirectional.csshader"));
//        material->SetShader(ShaderPass::k_point, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticBlinnPerVertexPoint.csshader"));
//        material->AddTexture(in_texture);
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateStaticDirectionalShadowMap(const std::string& in_uniqueId) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/StaticDirectionalShadowMap.csshader"));
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        
//#ifdef CS_ENABLE_DEBUGSHADOW
//        material->SetColourWriteEnabled(true);
//#else
//        material->SetColourWriteEnabled(false);
//#endif
//        
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimated(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_unlit);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimatedAmbient(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_unlit);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimatedBlinn(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        MaterialSPtr material(CreateCustom(in_uniqueId));
        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
        material->SetShadingType(Material::ShadingType::k_blinn);
        material->AddTexture(in_texture);
        material->SetTransparencyEnabled(false);
        material->SetCullFace(CullFace::k_back);
        material->SetFaceCullingEnabled(true);
        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimatedBlinnShadowed(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedAmbient.csshader"));
//        material->SetShader(ShaderPass::k_directional, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedBlinnShadowedDirectional.csshader"));
//        material->SetShader(ShaderPass::k_point, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedBlinnPoint.csshader"));
//        material->AddTexture(in_texture);
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimatedBlinnPerVertex(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedAmbient.csshader"));
//        material->SetShader(ShaderPass::k_directional, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedBlinnPerVertexDirectional.csshader"));
//        material->SetShader(ShaderPass::k_point, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedBlinnPerVertexPoint.csshader"));
//        material->AddTexture(in_texture);
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimatedBlinnPerVertexShadowed(const std::string& in_uniqueId, const TextureCSPtr& in_texture) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedAmbient.csshader"));
//        material->SetShader(ShaderPass::k_directional, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedBlinnPerVertexShadowedDirectional.csshader"));
//        material->SetShader(ShaderPass::k_point, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedBlinnPerVertexPoint.csshader"));
//        material->AddTexture(in_texture);
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        return material;
    }
    //---------------------------------------------------
    //---------------------------------------------------
    MaterialSPtr MaterialFactory::CreateAnimatedDirectionalShadowMap(const std::string& in_uniqueId) const
    {
        //TODO: Re-add support
        CS_LOG_FATAL("Unsupported: Yet to be implemented.");
        return nullptr;
        
//        MaterialSPtr material(CreateCustom(in_uniqueId));
//        ResourcePool* resourcePool = Application::Get()->GetResourcePool();
//        material->SetShader(ShaderPass::k_ambient, resourcePool->LoadResource<Shader>(StorageLocation::k_chilliSource, "Shaders/AnimatedDirectionalShadowMap.csshader"));
//        material->SetTransparencyEnabled(false);
//        material->SetCullFace(CullFace::k_back);
//        material->SetFaceCullingEnabled(true);
//        
//#ifdef CS_ENABLE_DEBUGSHADOW
//        material->SetColourWriteEnabled(true);
//#else
//        material->SetColourWriteEnabled(false);
//#endif
//        
//        return material;
    }
}
