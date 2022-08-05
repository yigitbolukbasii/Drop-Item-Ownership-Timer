
//Ara:

void CPythonItem::SetOwnership(DWORD dwVID, const char * c_pszName)

//Degistir:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
void CPythonItem::SetOwnership (DWORD dwVID, const char* c_pszName, int iSec, bool bUpdate)
#else
void CPythonItem::SetOwnership (DWORD dwVID, const char* c_pszName)
#endif


//Bul (ayni fonksiyon icinde):

rkTextTail.SetItemTextTailOwner(dwVID, c_pszName);


//Degistir:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	rkTextTail.SetItemTextTailOwner (dwVID, c_pszName, iSec, bUpdate);
#else
	rkTextTail.SetItemTextTailOwner (dwVID, c_pszName);
#endif

