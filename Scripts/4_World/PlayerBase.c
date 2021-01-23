modded class PlayerBase
{
    bool m_isInNoBZ = false;
    string m_NoBZ_Name = "";
    string m_NoBZ_Desc = "";

    bool GetIsInNoBZ()
    {
        return m_isInNoBZ;
    }

    string GetNoBZName()
    {
        return m_NoBZ_Name;
    }

    string GetNoBZDesc()
    {
        return m_NoBZ_Desc;
    }

    void SetIsInNoBZ( bool b, string name = "", string desc = "" )
    {
        m_isInNoBZ = b;
        m_NoBZ_Name = name;
        m_NoBZ_Desc = desc;
    }
}