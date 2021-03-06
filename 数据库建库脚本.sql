USE [AC_Login]
GO
/****** Object:  Table [dbo].[Login]    Script Date: 2016/6/9 13:49:55 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Login](
	[UserName] [varchar](50) NOT NULL,
	[PassWord] [varchar](50) NOT NULL
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Room_Detail_Info]    Script Date: 2016/6/9 13:49:56 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Room_Detail_Info](
	[Room_id] [nvarchar](50) NOT NULL,
	[Time] [nvarchar](60) NOT NULL,
	[Info] [nvarchar](255) NOT NULL,
	[Cost] [nvarchar](50) NOT NULL,
	[Energy] [nvarchar](50) NOT NULL,
	[User_id] [nvarchar](50) NOT NULL
) ON [PRIMARY]

GO
/****** Object:  Table [dbo].[Summary_Table]    Script Date: 2016/6/9 13:49:56 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Summary_Table](
	[Room_id] [nvarchar](50) NOT NULL,
	[Time_spend] [nvarchar](50) NOT NULL,
	[Cost] [nvarchar](50) NOT NULL,
	[On_Off_Times] [nvarchar](50) NOT NULL,
	[Temp_Adjust_Times] [nvarchar](50) NOT NULL,
	[Wind_Adjust_Times] [nvarchar](50) NOT NULL,
	[Room_Sche_Times] [nvarchar](50) NOT NULL,
	[User_id] [nvarchar](50) NOT NULL,
	[Time] [nvarchar](50) NOT NULL
) ON [PRIMARY]

GO
