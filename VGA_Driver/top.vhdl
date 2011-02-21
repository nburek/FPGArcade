----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:38:20 02/17/2011 
-- Design Name: 
-- Module Name:    top - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top is
    Port(
			red : out STD_LOGIC_VECTOR (2 downto 0);
			grn : out STD_LOGIC_VECTOR (2 downto 0);
			blue : out STD_LOGIC_VECTOR (1 downto 0);
			HS : out STD_LOGIC;
			VS : out STD_LOGIC;
			clk : in STD_LOGIC;
			Led : out STD_LOGIC_VECTOR (7 downto 0);
			sw : in STD_LOGIC_VECTOR (7 downto 0));
end top;

architecture Behavioral of top is

component clk25MHz
	Port (clk : in STD_LOGIC;
			sclk: out STD_LOGIC);
end component;

signal vCount : STD_LOGIC_VECTOR (9 downto 0);
signal hCount : STD_LOGIC_VECTOR (9 downto 0);
signal video_on_h, video_on_v : STD_LOGIC;
signal clk25 : STD_LOGIC;

begin 
	clock25MHz: clk25MHz port map (clk,clk25);
	Led <= "00000000";
	process
	
	begin
	
	wait until (clk25'EVENT) AND (clk25='1');
	
	IF (hCount = 799) THEN
		hCount <= "0000000000";
	ELSE
		hCount <= hCount + 1;
	END IF;
	
	IF (hCount <= 751) AND (hCount >= 656) THEN 
		HS <= '0';
	ELSE
		HS <= '1';
	END IF;
	
	IF (vCount >=521) AND (hCount >= 799) THEN
		vCount <= "0000000000";
	ELSIF (hCount=799) THEN
		vCount <= vCount+1;
	END IF;
	
	IF (vCount<=491) AND (vCount>=490) THEN -- 490 and 489
		VS <= '0';
	ELSE
		VS <= '1';
	END IF;
	
	IF (hCount <= 639) THEN
		video_on_h <= '1';
	ELSE
		video_on_h <= '0';
	END IF;
	
	IF (vCount <= 479) THEN
		video_on_v <= '1';
	ELSE
		video_on_v <= '0';
	END IF;
	
	
	IF (video_on_v = '1' AND video_on_h = '1') THEN
		red <= "111";
		grn <= "000";
		blue <= "00";
		--red <= sw(2 downto 0);
		--grn <= sw(5 downto 3);
		--blue <= sw(7 downto 6);
		--Led (7 downto 0) <= sw(7 downto 0);
	ELSE
		red <= "000";
		grn <= "000";
		blue <= "00";
		--Led(2 downto 0) <= "000";
		--Led(5 downto 3) <= "000";
		--Led(7 downto 6) <= "00";
	END IF;
	
	
	
	
	end process;
	


end Behavioral;

