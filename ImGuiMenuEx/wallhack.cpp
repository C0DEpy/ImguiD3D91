#include "stdafx.h"
#include "dx/dx9.h"
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_dx9.h"
#include "imgui/examples/imgui_impl_win32.h"
#include <stdio.h>
#include <time.h>

typedef HRESULT (WINAPI*_DrawIndexedPrimitive)(
	LPDIRECT3DDEVICE9 pDevice,
 D3DPRIMITIVETYPE Type,
 INT BaseVertexIndex,
 UINT MinIndex,
 UINT NumVertices,
 UINT StartIndex,
 UINT PrimitiveCount
);
_DrawIndexedPrimitive Original_DrawIndexedPrimitive;

BYTE DrawIndexedPrimitive_bytes;





if (wallhack) 
{

}