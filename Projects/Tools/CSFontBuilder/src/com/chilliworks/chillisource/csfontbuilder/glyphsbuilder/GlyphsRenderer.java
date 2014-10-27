/**
 * GlyphsRenderer.java
 * Chilli Source
 * Created by Ian Copland on 21/10/2014.
 * 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Tag Games Limited
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

package com.chilliworks.chillisource.csfontbuilder.glyphsbuilder;

import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.font.FontRenderContext;
import java.awt.font.GlyphMetrics;
import java.awt.font.GlyphVector;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.awt.image.ConvolveOp;
import java.awt.image.Kernel;

import com.chilliworks.chillisource.coreutils.Colour;
import com.chilliworks.chillisource.coreutils.Integer2;

/**
 * A collection of methods for creating a series of bitmap images containing
 * individual glyphs from a font.
 * 
 * @author Ian Copland
 */
public final class GlyphsRenderer
{
	/**
	 * Creates a series of bitmap images containing glyphs from the given
	 * font.
	 * 
	 * @author Ian Copland
	 * 
	 * @param in_options - The options for the gylph builder.
	 * 
	 * @return The glyph bitmap images. This will never be null.
	 */
	public static Glyphs render(GlyphsBuilderOptions in_options)
	{
		//get the font height and Y positions.
		Font font = new Font(in_options.m_fontName, in_options.m_fontStyle, in_options.m_fontSize);
		int fontLineHeight = calcFontHeight(font);
		int fontDescent = calcFontDescent(font);
		int fontY = fontLineHeight - fontDescent;
		
		//calculate the padding required for the effects applied to the font.
		Integer2 effectPadding = Integer2.ZERO;
		if (in_options.m_enableDropShadow == true)
		{
			effectPadding = Integer2.max(effectPadding, in_options.m_dropShadowOffset);
		}
		
		if (in_options.m_enableOutline == true)
		{
			effectPadding = Integer2.max(effectPadding, new Integer2(in_options.m_outlineSize, in_options.m_outlineSize));
		}
		
		if (in_options.m_enableGlow == true)
		{
			effectPadding = Integer2.max(effectPadding, new Integer2(in_options.m_glowSize, in_options.m_glowSize));
		}
		
		char[] glyphCharacters = in_options.m_characters.toCharArray();
		BufferedImage[] glyphImages = new BufferedImage[glyphCharacters.length];
		for (int i = 0; i < glyphCharacters.length; ++i)
		{
			char glyphChar = glyphCharacters[i];
			
			//get the information on the glyph.
			FontRenderContext fontRenderContext = new FontRenderContext(null, true, false);
			GlyphVector glyphVector = font.createGlyphVector(fontRenderContext, Character.toString(glyphChar));
			GlyphMetrics glyphMetrics = glyphVector.getGlyphMetrics(0);
			Rectangle2D glyphBounds = glyphMetrics.getBounds2D();
			
			//calculate the size of the image and position of the glyph.
			Integer2 imageSize = new Integer2((int)Math.ceil(glyphBounds.getMaxX()) + 2 * effectPadding.getX(), fontLineHeight + 2 * effectPadding.getY());
			Integer2 glyphPos = new Integer2(effectPadding.getX(), fontY + effectPadding.getY());
			
			//create the glyph image
			BufferedImage glyphImage = new BufferedImage(imageSize.getX(), imageSize.getY(), BufferedImage.TYPE_INT_ARGB);
			Graphics2D graphics = glyphImage.createGraphics();
			graphics.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
			
			//draw the drop shadow glyph if required.
			if (in_options.m_enableDropShadow == true)
			{
				Integer2 shadowGlyphPos = Integer2.add(glyphPos, in_options.m_dropShadowOffset);
				BufferedImage shadowImage = renderDropShadow(glyphVector, imageSize, shadowGlyphPos, in_options.m_dropShadowColour);
				graphics.drawImage(shadowImage, null, null);
			}
			
			//draw the glow glyph if required.
			if (in_options.m_enableGlow == true)
			{
				BufferedImage glowImage = renderGlow(glyphVector, imageSize, glyphPos, in_options.m_glowColour, in_options.m_glowSize);
				graphics.drawImage(glowImage, null, null);
			}
			
			//draw the outline glyph if required.
			if (in_options.m_enableOutline == true)
			{
				BufferedImage outlineImage = renderOutline(glyphVector, imageSize, glyphPos, in_options.m_outlineColour, in_options.m_outlineSize);
				graphics.drawImage(outlineImage, null, null);
			}
			
			//draw the glyph
			graphics.setColor(new Color((float)in_options.m_fontColour.getR(), (float)in_options.m_fontColour.getG(), (float)in_options.m_fontColour.getB(), (float)in_options.m_fontColour.getA()));
			graphics.drawGlyphVector(glyphVector, glyphPos.getX(), glyphPos.getY());
			glyphImages[i] = glyphImage;
		}
		
		return new Glyphs(glyphCharacters, glyphImages, in_options.m_fontSize, fontLineHeight, fontDescent, effectPadding);
	}
	/**
	 * Calculates the height of the given font.
	 * 
	 * @author Ian Copland
	 * 
	 * @param in_font - The font.
	 * 
	 * @return The height of the font.
	 */
	private static int calcFontHeight(Font in_font)
	{
		BufferedImage image = new BufferedImage(1, 1, BufferedImage.TYPE_INT_ARGB);
	    Graphics2D graphics1 = image.createGraphics();
	    FontMetrics fontMetrics = graphics1.getFontMetrics(in_font);
	    int fontHeight = fontMetrics.getHeight();
	    graphics1.dispose();
	    
	    return fontHeight;
	}
	/**
	 * Calculates the descent of the given font. This is the offset from the baseline of
	 * the font that most glyphs will be rendered at.
	 * 
	 * @author Ian Copland
	 * 
	 * @param in_font - The font.
	 * 
	 * @return The height of the font.
	 */
	private static int calcFontDescent(Font in_font)
	{
		BufferedImage image = new BufferedImage(1, 1, BufferedImage.TYPE_INT_ARGB);
	    Graphics2D graphics1 = image.createGraphics();
	    FontMetrics fontMetrics = graphics1.getFontMetrics(in_font);
	    int fontDescent = fontMetrics.getDescent();
	    graphics1.dispose();
	    
	    return fontDescent;
	}
	/**
	 * Renders the drop shadow for the given glyph vector.
	 * 
	 * @author Ian Copland
	 * 
	 * @param in_glyphVector - The glyph vector.
	 * @param in_imageSize - The size of the image the shadow should be rendered to.
	 * @param in_shadowPosition - The position of the shadow in the image.
	 * @param in_shadowColour - The colour of the shadow.
	 * 
	 * @return An image with the drop shadow rendered into it.
	 */
	private static BufferedImage renderDropShadow(GlyphVector in_glyphVector, Integer2 in_imageSize, Integer2 in_shadowPosition, Colour in_shadowColour)
	{
		BufferedImage image = new BufferedImage(in_imageSize.getX(), in_imageSize.getY(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D graphics = image.createGraphics();
		graphics.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
		
		graphics.setColor(new Color((float)in_shadowColour.getR(), (float)in_shadowColour.getG(), (float)in_shadowColour.getB(), (float)in_shadowColour.getA()));
		graphics.drawGlyphVector(in_glyphVector, in_shadowPosition.getX(), in_shadowPosition.getY());
		
		float BLUR_FACTOR = (1.0f / 9.0f);
		float[] blur = new float[]
		{
			BLUR_FACTOR, BLUR_FACTOR, BLUR_FACTOR,
			BLUR_FACTOR, BLUR_FACTOR, BLUR_FACTOR,
			BLUR_FACTOR, BLUR_FACTOR, BLUR_FACTOR
		};
		
		Kernel kernel = new Kernel(3, 3, blur);
		ConvolveOp op = new ConvolveOp(kernel, ConvolveOp.EDGE_NO_OP, null);
		return op.filter(image, null);
	}
	/**
	 * Renders the outline for the given glyph vector.
	 * 
	 * @author Ian Copland
	 * 
	 * @param in_glyphVector - The glyph vector.
	 * @param in_imageSize - The size of the image the outline should be rendered to.
	 * @param in_glyphPosition - The position of the outline in the image.
	 * @param in_outlineColour - The colour of the outline.
	 * @param in_outlineSize - The size of the outline.
	 * 
	 * @return An image with the outline rendered into it.
	 */
	private static BufferedImage renderOutline(GlyphVector in_glyphVector, Integer2 in_imageSize, Integer2 in_glyphPosition, Colour in_outlineColour, int in_outlineSize)
	{
		BufferedImage image = new BufferedImage(in_imageSize.getX(), in_imageSize.getY(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D graphics = image.createGraphics();
		graphics.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
		
		graphics.setColor(new Color((float)in_outlineColour.getR(), (float)in_outlineColour.getG(), (float)in_outlineColour.getB(), (float)in_outlineColour.getA()));
		
		for (int x = -in_outlineSize; x <= in_outlineSize; x+=in_outlineSize)
		{
			for (int y = -in_outlineSize; y <= in_outlineSize; y+=in_outlineSize)
			{
				graphics.drawGlyphVector(in_glyphVector, in_glyphPosition.getX() + x, in_glyphPosition.getY() + y);
			}
		}
		
		return image;
	}
	/**
	 * Renders the glow for the given glyph vector.
	 * 
	 * @author Ian Copland
	 * 
	 * @param in_glyphVector - The glyph vector.
	 * @param in_imageSize - The size of the image the glow should be rendered to.
	 * @param in_glyphPosition - The position of the glow in the image.
	 * @param in_glowColour - The colour of the glow.
	 * @param in_glowSize - The size of the glow.
	 * 
	 * @return An image with the glow rendered into it.
	 */
	private static BufferedImage renderGlow(GlyphVector in_glyphVector, Integer2 in_imageSize, Integer2 in_glyphPosition, Colour in_glowColour, int in_glowSize)
	{
		BufferedImage image = new BufferedImage(in_imageSize.getX(), in_imageSize.getY(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D graphics = image.createGraphics();
		graphics.setRenderingHint(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
		
		graphics.setColor(new Color((float)in_glowColour.getR(), (float)in_glowColour.getG(), (float)in_glowColour.getB(), (float)in_glowColour.getA()));
		
		for (int x = -in_glowSize; x <= in_glowSize; x+=in_glowSize)
		{
			for (int y = -in_glowSize; y <= in_glowSize; y+=in_glowSize)
			{
				graphics.drawGlyphVector(in_glyphVector, in_glyphPosition.getX() + x, in_glyphPosition.getY() + y);
			}
		}
		
		float BLUR_FACTOR = (1.0f / 9.0f);
		float[] blur = new float[]
		{
			BLUR_FACTOR, BLUR_FACTOR, BLUR_FACTOR,
			BLUR_FACTOR, BLUR_FACTOR, BLUR_FACTOR,
			BLUR_FACTOR, BLUR_FACTOR, BLUR_FACTOR
		};
		
		Kernel kernel = new Kernel(3, 3, blur);
		ConvolveOp op = new ConvolveOp(kernel, ConvolveOp.EDGE_NO_OP, null);
		return op.filter(image, null);
	}
}
