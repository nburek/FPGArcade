----------------------------------------------------------------------------------
-- Company: Loras College
-- Engineer: Nick Burek
-- 
-- Create Date:    18:38:20 02/17/2011 
-- Design Name: 
-- Module Name:    top - Behavioral 
-- Project Name: VGA_Driver
-- Target Devices: nexys2
-- Tool versions: 
-- Description: This module is meant to be a simple VGA driver example. It will 
-- 		
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

entity top is
    Port(
			VGA_Red : out STD_LOGIC_VECTOR (2 downto 0);
			VGA_Green : out STD_LOGIC_VECTOR (2 downto 0);
			VGA_Blue : out STD_LOGIC_VECTOR (1 downto 0);
			HSync : out STD_LOGIC;
			VSync : out STD_LOGIC;
			clk : in STD_LOGIC;
			BlockPosition : in STD_LOGIC_VECTOR (0 to 19));
end top;

architecture Behavioral of top is

component clk25MHz
	Port (clk : in STD_LOGIC;
			sclk: out STD_LOGIC);
end component;

signal vCount : STD_LOGIC_VECTOR (9 downto 0);
signal hCount : STD_LOGIC_VECTOR (9 downto 0);
signal clk25 : STD_LOGIC;

begin 
	clock25MHz: clk25MHz port map (clk,clk25);
	
	process (clk25)
	
	begin
	
	-- timing diagram for the horizontal synch signal (HS)
	-- 0                               656    752     799 (pixels)
	-- --------------------------------|______|----------
	-- timing diagram for the vertical synch signal (VS)
	-- 0                        490    492            521 (lines)
	-- -------------------------|______|-----------------

	IF clk25'EVENT AND clk25='1' THEN
	
		
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
			
			IF (vCount >= BlockPosition(10 to 19) AND vCount <= (conv_integer(BlockPosition(10 to 19)) + 30)) THEN
				IF (hCount>=BlockPosition(0 to 9) AND hCount <= (conv_integer(BlockPosition(0 to 9)) + 30)) THEN
					VGA_Red <= "111";
					VGA_Green <= "111";
					VGA_Blue <= "11";
				ELSE
					VGA_Red <= "000";
					VGA_Green <= "000";
					VGA_Blue <= "00";
				END IF;
			ELSE
				VGA_Red <= "000";
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

