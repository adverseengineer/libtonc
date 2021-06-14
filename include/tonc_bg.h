//
//  Tiled background stuff
//
//! \file tonc_bg.h
//! \author J Vijn, Nick Sells
//! \date 20060604 - 20080311, 20210512
//

#ifndef TONC_BG
#define TONC_BG

#include "tonc_memmap.h"
#include "tonc_video.h"

// --- single-tile routines ---
INLINE void bg_fill(u32 sbb, SCR_ENTRY se);
INLINE void bg_plot(u32 sbb, u32 x, u32 y, SCR_ENTRY se);
INLINE void bg_hline(u32 sbb, u32 x0, u32 x1, u32 y, SCR_ENTRY se);
INLINE void bg_vline(u32 sbb, u32 x, u32 y0, u32 y1, SCR_ENTRY se);

INLINE void bg_rect(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se);
INLINE void bg_frame(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se);
INLINE void bg_window(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0);

// --- meta-tile variants ---
INLINE void bg_fill_m(u32 sbb, SCR_ENTRY se0);
INLINE void bg_plot_m(u32 sbb, u32 x, u32 y, SCR_ENTRY se0);
INLINE void bg_hline_m(u32 sbb, u32 x0, u32 x1, u32 y, SCR_ENTRY se0);
INLINE void bg_vline_m(u32 sbb, u32 x, u32 y0, u32 y1, SCR_ENTRY se0);

INLINE void bg_rect_m(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0);
INLINE void bg_frame_m(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0);
INLINE void bg_window_m(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0);



//! Fill screenblock \a sbb with \a se
INLINE void bg_fill(u32 sbb, SCR_ENTRY se)
{
	memset32(se_mem[sbb], dup16(se), SBB_SIZE / 4);
}

//! Plot a screen entry at (\a x,\a y) of screenblock \a sbb.
//! NOTE: treats four 32x32 screenblocks as a single 64x64 one
INLINE void bg_plot(u32 sbb, u32 x, u32 y, SCR_ENTRY se)
{
	u32 bottom = (y & 32) ? 2048 : 0;
	u32 right = (x & 32) ? 1024 : 0;
	u32 row = y & 31;
	u32 col = x & 31;
	se_mem[sbb][col + row * 32 + bottom + right] = se;
}

//! Plot a horizontal line of tiles on screenblock \a sbb
INLINE void bg_hline(u32 sbb, u32 x0, u32 x1, u32 y, SCR_ENTRY se)
{
	for(u32 ix = x0; ix < x1; ix++)
		bg_plot(sbb, ix, y, se);
}

//! Plot a vertical line of tiles on screenblock \a sbb
INLINE void bg_vline(u32 sbb, u32 x, u32 y0, u32 y1, SCR_ENTRY se)
{
	for(u32 iy = y0; iy < y1; iy++)
		bg_plot(sbb, x, iy, se);
}

//! Fill a rectangle on \a sbb with \a se.
INLINE void bg_rect(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se)
{
	bmp16_rect(left, top, right, bottom, se, se_mem[sbb], 32*2);
}

//! Create a border on \a sbb with \a se.
INLINE void bg_frame(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se)
{
	bmp16_frame(left, top, right, bottom, se, se_mem[sbb], 32*2);
}

//! Create a framed rectangle on \a sbb with the nine tiles starting at \a se0
INLINE void bg_window(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0)
{
	//corners
	bg_plot(sbb, left, top, se0);
	bg_plot(sbb, right, top, se0 + 2);
	bg_plot(sbb, left, bottom, se0 + 6);
	bg_plot(sbb, right, bottom, se0 + 8);
	//horizontal edges
	bg_hline(sbb, left + 1, right - 1, top, se0 + 1);
	bg_hline(sbb, left + 1, right - 1, bottom, se0 + 7);
	//vertical edges
	bg_vline(sbb, left, top + 1, bottom - 1, se0 + 3);
	bg_vline(sbb, right, top + 1, bottom - 1, se0 + 5);
	//center
	bg_rect(sbb, left + 1, top + 1, right - 1, bottom - 1, se0 + 4);
}

//! Fill screenblock \a sbb with the meta-tile starting at \a s0
INLINE void bg_fill_m(u32 sbb, SCR_ENTRY se0) {
	for(u32 iy = 0; iy < 16; iy++)
		bg_hline_m(sbb, 0, 15, iy, se0);
}

//! Plot the meta-tile starting at \a se0 at (\a x,\a y) of screenblock \a sbb
INLINE void bg_plot_m(u32 sbb, u32 x, u32 y, SCR_ENTRY se0)
{
	bg_plot(sbb, x * 2, y * 2, se0);
	bg_plot(sbb, x * 2 + 1, y * 2, se0 + 1);
	bg_plot(sbb, x * 2, y * 2 + 1, se0 + 2);
	bg_plot(sbb, x * 2 + 1, y * 2 + 1, se0 + 3);
}

//! Plot a horizontal line on screenblock \a sbb with the meta-tile starting at \a se0
INLINE void bg_hline_m(u32 sbb, u32 x0, u32 x1, u32 y, SCR_ENTRY se0)
{
	for(u32 ix = x0; ix <= x1; ix++)
		bg_plot_m(sbb, ix, y, se0);
}

//! Plot a vertical line on screenblock \a sbb with the meta-tile starting at \a se0
INLINE void bg_vline_m(u32 sbb, u32 x, u32 y0, u32 y1, SCR_ENTRY se0)
{
	for(u32 iy = y0; iy <= y1; iy++)
		bg_plot_m(sbb, x, iy, se0);
}

//! Fill a rectangle on \a sbb with the meta-tile starting at \a se0
INLINE void bg_rect_m(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0)
{
	for(u32 iy = top; iy <= bottom; iy++)
		bg_hline_m(sbb, left, right, iy, se0);
}

//! Create a border on \a sbb with the meta-tile starting at \a se0
INLINE void bg_frame_m(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0)
{
	bg_hline_m(sbb, left, right, top, se0);
	bg_hline_m(sbb, left, right, bottom, se0);
	bg_vline_m(sbb, left, top + 1, bottom - 1, se0);
	bg_vline_m(sbb, right, top + 1, bottom - 1, se0);
}

//! Create a framed rectangle on \a sbb with the nine meta-tiles starting at \a se0
INLINE void bg_window_m(u32 sbb, u32 left, u32 top, u32 right, u32 bottom, SCR_ENTRY se0)
{
	//corners
	bg_plot_m(sbb, left, top, se0);
	bg_plot_m(sbb, right, top, se0 + 8);
	bg_plot_m(sbb, left, bottom, se0 + 24);
	bg_plot_m(sbb, right, bottom, se0 + 32);
	//horizontal edges
	bg_hline_m(sbb, left + 1, right - 1, top, se0 + 4);
	bg_hline_m(sbb, left + 1, right - 1, bottom, se0 + 28);
	//vertical edges
	bg_vline_m(sbb, left, top + 1, bottom - 1, se0 + 12);
	bg_vline_m(sbb, right, top + 1, bottom - 1, se0 + 20);
	//center
	bg_rect_m(sbb, left + 1, top + 1, right - 1, bottom - 1, se0 + 16);
}

#endif //TONC_BG