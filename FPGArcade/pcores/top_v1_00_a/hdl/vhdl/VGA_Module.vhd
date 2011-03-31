----------------------------------------------------------------------------------
-- Company: Loras College
-- Engineer: Nick Burek
-- 
-- Create Date:    07:42:04 03/24/2011 
-- Design Name: 
-- Module Name:    VGA_Module - Behavioral 
-- Project Name: FPGArcade
-- Target Devices: Nexys2 Board
-- Tool versions: 
-- Description: Handles the sync timing and outputs for the VGA signals
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
			clk50Mhz : in STD_LOGIC;
			graphicsInstruction : in STD_LOGIC_VECTOR(31 downto 0));
end top;

architecture Behavioral of top is

component clk25MHz
	Port (clk : in STD_LOGIC;
			sclk: out STD_LOGIC);
end component;

component Video_RAM
    Port ( instruction : in  STD_LOGIC_VECTOR(31 downto 0);
           positionX : in  STD_LOGIC_VECTOR(9 downto 0);
           positionY : in  STD_LOGIC_VECTOR(8 downto 0);
           currentPixel : out  STD_LOGIC_VECTOR(7 downto 0));
end component;

signal vCount : STD_LOGIC_VECTOR (8 downto 0);
signal hCount : STD_LOGIC_VECTOR (9 downto 0);
signal clk25 : STD_LOGIC;
signal pixelX : STD_LOGIC_VECTOR (9 downto 0);
signal pixelY : STD_LOGIC_VECTOR (8 downto 0);
signal currentPixel : STD_LOGIC_VECTOR(7 downto 0);



begin 
	clock25MHz: clk25MHz port map (clk50Mhz,clk25);
	videoRam : Video_RAM port map (graphicsInstruction,pixelX,pixelY,currentPixel);
	
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
				vCount <= "000000000"; -- done outputing the screen, start over
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
		
		
		IF (hCount<=639 AND vCount<=479) THEN -- are we within the valid pixel range
			pixelX <= hCount;
			pixelY <= vCount;
			VGA_Red <= currentPixel(2 downto 0);
			VGA_Green <= currentPixel(5 downto 3);
			VGA_Blue <= currentPixel(7 downto 6);
		ELSE
			-- turn off the pixel out data because it is either on the front/back porch or the pulse signal
			VGA_Red <= "000";
			VGA_Green <= "000";
			VGA_Blue <= "00";
		END IF;
	
	END IF;
	
	
	end process;
	


end Behavioral;

