
//Ara

		void	SetOwnership(DWORD dwVID, const char * c_pszName);


//Degistir

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
		void SetOwnership (DWORD dwVID, const char* c_pszName, int iSec, bool bUpdate);
#else
		void SetOwnership (DWORD dwVID, const char* c_pszName);
#endif

