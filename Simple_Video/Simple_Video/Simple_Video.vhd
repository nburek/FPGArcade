----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:12:48 03/05/2011 
-- Design Name: 
-- Module Name:    Simple_Video - Behavioral 
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



entity Simple_Video is
    Port ( 
			VGA_Red : out STD_LOGIC_VECTOR (2 downto 0);
			VGA_Green : out STD_LOGIC_VECTOR (2 downto 0);
			VGA_Blue : out STD_LOGIC_VECTOR (1 downto 0);
			HSync : out STD_LOGIC;
			VSync : out STD_LOGIC;
			clk50 : in STD_LOGIC;
			sw : in STD_LOGIC_VECTOR (7 downto 0);
			btn : in STD_LOGIC_VECTOR(3 downto 0));
			
end Simple_Video;

architecture Behavioral of Simple_Video is

component clk25MHz
	Port (clk : in STD_LOGIC;
			sclk: out STD_LOGIC);
end component;

component slowClock
    Port ( clk : in  STD_LOGIC;
           sclk : out  STD_LOGIC);
end component;

signal vCount : STD_LOGIC_VECTOR (9 downto 0);
signal hCount : STD_LOGIC_VECTOR (9 downto 0);
signal clk25 : STD_LOGIC;
signal clkSlow : STD_LOGIC;
signal blockXPosition : std_logic_vector(0 to 9) := "0000000100";
signal blockYPosition : std_logic_vector(0 to 9) := "0000000100";

begin
	clock25MHz: clk25MHz port map (clk50,clk25);
	verySlowClock : slowClock port map(clk50, clkSlow);
	
	process (clkSlow)
	begin
		IF clkSlow'EVENT AND clkSlow='1' THEN
			blockXPosition <= blockXPosition + 1;
			
			IF (blockXPosition = "0101000000") THEN
				blockXPosition <= "0000000000";
			END IF;
		END IF;
	end process;
	
	process (clk25)
	
	begin
	
	-- timing diagram for the horizontal synch signal (HS)
	-- 0                               656    752     799 (pixels)
	-- --------------------------------|______|----------
	-- timing diagram for the vertical synch signal (VS)
	-- 0                        490    492            521 (lines)
	-- -------------------------|______|-----------------

	IF clk25'EVENT AND clk25='1' THEN
	
		--blockXPosition(0 to 7) <= sw;
		blockYPosition(0 to 3) <= btn;
		IF (hCount = 799) THEN
			-- done with this row, move down to the next one
			hCount <= "0000000000"; 
			
			IF (vCount = 521) THEN
				vCount <= "0000000000"; -- done outputing the screen, start over
			ELSE
				vCount <= vCount + 1; -- increment the row count to track which row you're on
			END IF;
			
		ELSE
			hCount <= hCount + 1;
		END IF;
		
		IF (hCount <= 751) AND (hCount >= 656) THEN -- is it time to pulse the horizontal sync signal low
			HSync <= '0';
		ELSE
			HSync <= '1';
		END IF;
		
		
		IF (vCount<=491) AND (vCount>=490) THEN -- is it time to pulse the vertical sync signal low
			VSync <= '0';
		ELSE
			VSync <= '1';
		END IF;
		
		
		IF (hCount <= 639 AND vCount <= 479) THEN -- are we within the valid pixel range
			
			IF (vCount >= blockYPosition AND vCount <= (conv_integer(blockYPosition) + 30)) THEN
				IF (hCount>=blockXPosition AND hCount <= (conv_integer(blockXPosition) + 30)) THEN
					VGA_Red <= "000";
					VGA_Green <= "000";
					VGA_Blue <= "11";
				ELSE
					VGA_Red <= "111";
					VGA_Green <= "000";
					VGA_Blue <= "00";
				END IF;
			ELSE
				VGA_Red <= "111";
				VGA_Green <= "000";
				VGA_Blue <= "00";
			END IF;
			
		ELSE
			-- turn off the pixel out data because it is either on the front/back porch or the pulse signal
			VGA_Red <= "000";
			VGA_Green <= "000";
			VGA_Blue <= "00";
		END IF;
	
	END IF;
	
	
	end process;

end Behavioral;

