
//Ara (CItem constructor):

	m_dwMaskVnum(0), m_dwSIGVnum (0)


//Altina ekle:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	, m_pkUpdateOwnershipEvent (NULL)
#endif


//Ara (void CItem::Initialize()):
	m_pkOwnershipEvent = NULL;


//Altina ekle:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	m_pkUpdateOwnershipEvent = NULL;
#endif


//Ara (void CItem::Destroy()):
	event_cancel(&m_pkOwnershipEvent);


//Altina ekle:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	event_cancel (&m_pkUpdateOwnershipEvent);
#endif


//Ara (void CItem::EncodeInsertPacket(LPENTITY ent)):

	if (m_pkOwnershipEvent != NULL)
	{
		item_event_info * info = dynamic_cast<item_event_info *>(m_pkOwnershipEvent->info);

		if ( info == NULL )
		{
			sys_err( "CItem::EncodeInsertPacket> <Factor> Null pointer" );
			return;
		}

		TPacketGCItemOwnership p;

		p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
		p.dwVID = m_dwVID;
		strlcpy(p.szName, info->szOwnerName, sizeof(p.szName));

		d->Packet(&p, sizeof(TPacketGCItemOwnership));
	}


//Degistir:

	if (m_pkOwnershipEvent != NULL)
	{
		item_event_info * info = dynamic_cast<item_event_info*> (m_pkOwnershipEvent->info);

		if (info == NULL)
		{
			sys_err ("CItem::EncodeInsertPacket> <Factor> Null pointer");
			return;
		}

		TPacketGCItemOwnership p;

		p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
		p.dwVID = m_dwVID;
		strlcpy (p.szName, info->szOwnerName, sizeof (p.szName));
#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
		p.iSec = m_iSec;
		p.bUpdate = false;
#endif

		d->Packet (&p, sizeof (TPacketGCItemOwnership));
	}


//Ara (EVENTFUNC(ownership_event)):

	pkItem->SetOwnershipEvent (NULL);


//Altina ekle:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	LPEVENT updateOwnershipEvent = pkItem->GetUpdateOwnershipEvent();
	if (updateOwnershipEvent)
	{
		event_cancel (&updateOwnershipEvent);
		pkItem->SetUpdateOwnershipEvent (NULL);
	}
#endif


//Ara (EVENTFUNC(ownership_event)):
	TPacketGCItemOwnership p;

	p.bHeader	= HEADER_GC_ITEM_OWNERSHIP;
	p.dwVID	= pkItem->GetVID();
	p.szName[0]	= '\0';

	pkItem->PacketAround(&p, sizeof(p));


//Degistir:

	TPacketGCItemOwnership p;

	p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
	p.dwVID = pkItem->GetVID();
	p.szName[0] = '\0';
#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	p.iSec = 0;
	p.bUpdate = false;
#endif

	pkItem->PacketAround (&p, sizeof (p));


//Ara:

void CItem::SetOwnershipEvent(LPEVENT pkEvent)
{
	m_pkOwnershipEvent = pkEvent;
}


//Altina ekle:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
EVENTFUNC (update_ownership_event)
{
	update_ownership_info* info = dynamic_cast<update_ownership_info*> (event->info);

	if (info == NULL)
	{
		sys_err ("update_ownership_event> <Factor> Null pointer");
		return 0;
	}

	LPITEM pkItem = info->item;

	if (pkItem)
	{
		LPEVENT ownershipEvent = pkItem->GetOwnershipEvent();
		if (ownershipEvent)
		{
			LPEVENT updateOwnershipEvent = pkItem->GetUpdateOwnershipEvent();
			if (updateOwnershipEvent)
			{
				int iRemainingOwnershipDuration = rint ((pkItem->GetOwnershipDuration() - event_processing_time (ownershipEvent) / passes_per_sec));
				TPacketGCItemOwnership p;

				p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
				p.dwVID = pkItem->GetVID();
				strlcpy (p.szName, info->szOwnerName, sizeof (p.szName));
				p.iSec = iRemainingOwnershipDuration;
				p.bUpdate = true;

				pkItem->PacketAround (&p, sizeof (p));

				if (iRemainingOwnershipDuration < 0)
				{
					return 0;
				}
				return iRemainingOwnershipDuration;
			}
		}
	}
	return 0;
}

void CItem::SetUpdateOwnershipEvent (LPEVENT pkEvent)
{
	m_pkUpdateOwnershipEvent = pkEvent;
}
#endif


//Ara (void CItem::SetOwnership(LPCHARACTER ch, int iSec)):

	if (!ch)
	{
		if (m_pkOwnershipEvent)
		{
			event_cancel(&m_pkOwnershipEvent);
			m_dwOwnershipPID = 0;

			TPacketGCItemOwnership p;

			p.bHeader	= HEADER_GC_ITEM_OWNERSHIP;
			p.dwVID	= m_dwVID;
			p.szName[0]	= '\0';

			PacketAround(&p, sizeof(p));
		}
		return;
	}


//Degistir:

	if (!ch)
	{
		if (m_pkOwnershipEvent)
		{
			event_cancel (&m_pkOwnershipEvent);
			m_dwOwnershipPID = 0;

			TPacketGCItemOwnership p;

			p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
			p.dwVID = m_dwVID;
			p.szName[0] = '\0';
#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
			p.iSec = 0;
			p.bUpdate = false;
#endif

			PacketAround (&p, sizeof (p));
		}
		return;
	}


//Ara (same function):

	if (iSec <= 10)
		iSec = 30;

//Altina ekle:

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	m_iSec = iSec;
#endif


//Ara (same function):
	TPacketGCItemOwnership p;

	p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
	p.dwVID = m_dwVID;
	strlcpy(p.szName, ch->GetName(), sizeof(p.szName));

	PacketAround(&p, sizeof(p));


//Degistir:

	TPacketGCItemOwnership p;

	p.bHeader = HEADER_GC_ITEM_OWNERSHIP;
	p.dwVID = m_dwVID;
	strlcpy (p.szName, ch->GetName(), sizeof (p.szName));
#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	p.iSec = m_iSec;
	p.bUpdate = false;
#endif

	PacketAround (&p, sizeof (p));


//Ekle (end of function, after PacketAround call):

#ifdef ENABLE_OWNERSHIP_DURATION_TIMER
	update_ownership_info* updateOwnershipInfo = AllocEventInfo<update_ownership_info>();
	strlcpy (updateOwnershipInfo->szOwnerName, ch->GetName(), sizeof (updateOwnershipInfo->szOwnerName));
	updateOwnershipInfo->item = this;

	SetUpdateOwnershipEvent (event_create (update_ownership_event, updateOwnershipInfo, PASSES_PER_SEC (1)));
#endif

