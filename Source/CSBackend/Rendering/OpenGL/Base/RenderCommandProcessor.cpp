//
//  The MIT License (MIT)
//
//  Copyright (c) 2016 Tag Games Limited
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

#include <CSBackend/Rendering/OpenGL/Base/RenderCommandProcessor.h>

#include <CSBackend/Rendering/OpenGL/Model/GLMesh.h>
#include <CSBackend/Rendering/OpenGL/Shader/GLShader.h>
#include <CSBackend/Rendering/OpenGL/Texture/GLTexture.h>

#include <ChilliSource/Rendering/RenderCommand/RenderCommandList.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/LoadMaterialGroupRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/LoadMeshRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/LoadShaderRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/LoadTextureRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/UnloadMaterialGroupRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/UnloadMeshRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/UnloadShaderRenderCommand.h>
#include <ChilliSource/Rendering/RenderCommand/Commands/UnloadTextureRenderCommand.h>

namespace CSBackend
{
    namespace OpenGL
    {
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::Process(const ChilliSource::RenderCommandQueue& renderCommandQueue) noexcept
        {
            for (const auto& renderCommandList : renderCommandQueue)
            {
                for (const auto& renderCommand : renderCommandList->GetOrderedList())
                {
                    switch (renderCommand->GetType())
                    {
                        case ChilliSource::RenderCommand::Type::k_loadShader:
                            LoadShader(static_cast<const ChilliSource::LoadShaderRenderCommand*>(renderCommand));
                            break;
                        case ChilliSource::RenderCommand::Type::k_loadTexture:
                            LoadTexture(static_cast<const ChilliSource::LoadTextureRenderCommand*>(renderCommand));
                            break;
                        case ChilliSource::RenderCommand::Type::k_loadMaterialGroup:
                            // Do nothing in OpenGL 2.0 / ES 2.0
                            break;
                        case ChilliSource::RenderCommand::Type::k_loadMesh:
                            LoadMesh(static_cast<const ChilliSource::LoadMeshRenderCommand*>(renderCommand));
                            break;
                        case ChilliSource::RenderCommand::Type::k_unloadShader:
                            UnloadShader(static_cast<const ChilliSource::UnloadShaderRenderCommand*>(renderCommand));
                            break;
                        case ChilliSource::RenderCommand::Type::k_unloadTexture:
                            UnloadTexture(static_cast<const ChilliSource::UnloadTextureRenderCommand*>(renderCommand));
                            break;
                        case ChilliSource::RenderCommand::Type::k_unloadMaterialGroup:
                            // Do nothing in OpenGL 2.0 / ES 2.0
                            break;
                        case ChilliSource::RenderCommand::Type::k_unloadMesh:
                            UnloadMesh(static_cast<const ChilliSource::UnloadMeshRenderCommand*>(renderCommand));
                            break;
                        default:
                            CS_LOG_FATAL("Unknown render command.");
                            break;
                    }
                }
            }
        }
        
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::LoadShader(const ChilliSource::LoadShaderRenderCommand* renderCommand) noexcept
        {
            auto renderShader = renderCommand->GetRenderShader();
            
            //TODO: Should be pooled.
            auto glShader = new GLShader(renderCommand->GetVertexShader(), renderCommand->GetFragmentShader());
            
            renderShader->SetExtraData(glShader);
            m_contextState.SetRenderShader(nullptr);
        }
        
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::LoadTexture(const ChilliSource::LoadTextureRenderCommand* renderCommand) noexcept
        {
            auto renderTexture = renderCommand->GetRenderTexture();
            
            //TODO: Should be pooled.
            auto glTexture = new GLTexture(renderCommand->GetTextureData(), renderCommand->GetTextureDataSize(), renderTexture->GetDimensions(), renderTexture->GetImageFormat(),
                                           renderTexture->GetImageCompression(), renderTexture->GetFilterMode(), renderTexture->GetWrapModeS(), renderTexture->GetWrapModeT(),
                                           renderTexture->IsMipmapped());
            
            renderTexture->SetExtraData(glTexture);
            m_contextState.SetRenderTexture(nullptr);
        }
        
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::LoadMesh(const ChilliSource::LoadMeshRenderCommand* renderCommand) noexcept
        {
            auto renderMesh = renderCommand->GetRenderMesh();
            
            //TODO: Should be pooled.
            auto glMesh = new GLMesh(renderMesh->GetPolygonType(), renderMesh->GetVertexFormat(), renderMesh->GetIndexFormat(), renderCommand->GetVertexData(), renderCommand->GetVertexDataSize(),
                                     renderCommand->GetIndexData(), renderCommand->GetIndexDataSize());
            
            renderMesh->SetExtraData(glMesh);
            m_contextState.SetRenderMesh(nullptr);
        }
        
        
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::UnloadShader(const ChilliSource::UnloadShaderRenderCommand* renderCommand) noexcept
        {
            m_contextState.SetRenderShader(nullptr);
            
            auto renderShader = renderCommand->GetRenderShader();
            auto glShader = reinterpret_cast<GLShader*>(renderShader->GetExtraData());
            
            CS_SAFEDELETE(glShader);
        }
        
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::UnloadTexture(const ChilliSource::UnloadTextureRenderCommand* renderCommand) noexcept
        {
            m_contextState.SetRenderTexture(nullptr);
            
            auto renderTexture = renderCommand->GetRenderTexture();
            auto glTexture = reinterpret_cast<GLTexture*>(renderTexture->GetExtraData());
            
            CS_SAFEDELETE(glTexture);
        }
        
        //------------------------------------------------------------------------------
        void RenderCommandProcessor::UnloadMesh(const ChilliSource::UnloadMeshRenderCommand* renderCommand) noexcept
        {
            m_contextState.SetRenderMesh(nullptr);
            
            auto renderMesh = renderCommand->GetRenderMesh();
            auto glMesh = reinterpret_cast<GLMesh*>(renderMesh->GetExtraData());
            
            CS_SAFEDELETE(glMesh);
        }
    }
}