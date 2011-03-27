----------------------------------------------------------------------------------
-- Company: Loras College
-- Engineer: Nick Burek
--
-- Create Date:    07:50:07 03/24/2011 
-- Design Name: 
-- Module Name:    Video_RAM - Behavioral 
-- Project Name: FPGArcade
-- Target Devices: Nexys2 Board
-- Tool versions: 
-- Description: Stores all the data for the tile based graphics engine. Handles 
--			looking up which color the pixel needs to be set on based on the background
--			map and the moveable block's positions. Also handles the op code instructions
--			for changing tile/block data.
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


entity Video_RAM is
    Port ( clk50Mhz : in  STD_LOGIC;
           instruction : in  STD_LOGIC_VECTOR(31 downto 0);
           positionX : in  STD_LOGIC_VECTOR(9 downto 0);
           positionY : in  STD_LOGIC_VECTOR(8 downto 0);
           currentPixel : out  STD_LOGIC_VECTOR(7 downto 0));
end Video_RAM;

architecture Behavioral of Video_RAM is

-- start creating the tile set
type tileSet is array(4095 downto 0) of STD_LOGIC_VECTOR(7 downto 0); -- 64 tiles at 8x8 pixels, each pixel being 8 bits
signal tileMap : tileSet;

-- start creating the background map
type backgroundColumn is array (59 downto 0) of STD_LOGIC_VECTOR(5 downto 0);
type backgroundSet is array (79 downto 0) of backgroundColumn;
signal backgroundMap : backgroundSet;

-- start creating the moving blocks
type moving_blocks_x is array (15 downto 0) of STD_LOGIC_VECTOR(9 downto 0); -- the x coordinates of all the moving tile
type moving_blocks_y is array (15 downto 0) of STD_LOGIC_VECTOR(8 downto 0); -- the y coordinates of all the moving tile
signal movingBlocksX : moving_blocks_x := (others => "1010000000");
signal movingBlocksY : moving_blocks_y;
type transparencySet is array(1023 downto 0) of STD_LOGIC;
signal movingBlocksTransparencyMap : transparencySet;
type movingTilesSet is array (15 downto 0) of STD_LOGIC_VECTOR(5 downto 0);
signal movingTilesMap : movingTilesSet;

-- used when getting the current pixel to display
signal tileNumber : STD_LOGIC_VECTOR(5 downto 0);
signal pixelX : STD_LOGIC_VECTOR(2 downto 0);
signal pixelY : STD_LOGIC_VECTOR(2 downto 0);


begin
	
	tileMap(0) <= "00000111";
	tileMap(9) <= "00000111";
	tileMap(18) <= "00000111";
	tileMap(27) <= "00000111";
	tileMap(36) <= "00000111";
	tileMap(45) <= "00000111";
	tileMap(54) <= "00000111";
	tileMap(63) <= "00000111";
	tileMap(127 downto 64) <= (others => "11000000");
	tileMap(191 downto 128) <= (others => "00111000");
	
	movingTilesMap(0) <= "000001";
	movingBlocksX(0) <= "0000011011";
	movingBlocksY(0) <= "000101101";
	movingBlocksTransparencyMap(31 downto 0) <= "11111111111111111111111111111111";
	
	movingTilesMap(1) <= "000010";
	movingBlocksX(1) <= "0000011011";
	movingBlocksY(1) <= "000001101";
	--movingBlocksTransparencyMap(127 downto 96) <= (others => '1');
	
	backgroundMap(15)(15) <= "000001";
	
	--process that loads in the current pixel based on what x and y position the vga driver is trying to output
	process (positionX, positionY, backgroundMap,tileMap)
	begin
	
		-- gets the tile number referenced by the background block at this location
		tileNumber <= backgroundMap(conv_integer(positionX(9 downto 3)))(conv_integer(positionY(8 downto 3)));
		pixelX <= positionX(2 downto 0); 
		pixelY <= positionY(2 downto 0);
		
		-- start checking if it's inside a moving block
		for i in 15 downto 0 loop
			--tempX <= conv_integer(movingBlocksX(i)(9 downto 0));
			--tempY <= conv_integer(movingBlocksY(i)(8 downto 0));
			-- check if it's inside this moving block
			if (positionX>=conv_integer(movingBlocksX(i)(9 downto 0)) and 
					positionX<=(conv_integer(movingBlocksX(i)(9 downto 0))+7) and
					positionY>=conv_integer(movingBlocksY(i)(8 downto 0)) and 
					positionY<=(conv_integer(movingBlocksY(i)(8 downto 0))+7)) then
				
				-- check if it's on a transparent bit
				if (movingBlocksTransparencyMap(conv_integer(conv_std_logic_vector(i,6) & conv_std_logic_vector(conv_integer(positionY-conv_integer(movingBlocksY(i)(8 downto 0))),3) & conv_std_logic_vector(conv_integer(positionX-conv_integer(movingBlocksX(i)(9 downto 0))),3))) = '0') then
					tileNumber <= movingTilesMap(i); -- get which tile map to use
					pixelX <= positionX - conv_integer(movingBlocksX(i)(9 downto 0));
					pixelY <= positionY - conv_integer(movingBlocksY(i)(8 downto 0));
				end if; -- end if pixel is not set to transparent
			end if; -- end if inside moving block
		end loop;
		
		-- now that we know which tile we need to use and which pixel from that tile we can output it
		currentPixel <= tileMap(conv_integer(tileNumber & pixelY & pixelX));
	
	end process;
	
	
	-- process that handles the execution of instructions
	process (instruction)
	begin
		case instruction(31 downto 29) is 
			when "000" => -- set pixel in tile
				--tileMap(conv_integer(instruction(19 downto 8))) <= instruction(7 downto 0);
			when "001" => -- set row transparency on moveable block
				--movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "111") downto conv_integer(instruction(6 downto 0) & "000")) <= instruction(14 down to 7);
			when "010" => -- change location of moveable block
				--movingBlocksX(conv_integer(instruction(22 downto 19))) <= instruction(9 downto 0);
				--movingBlocksY(conv_integer(instruction(22 downto 19))) <= instruction(18 downto 10);
			when "011" => -- set moveable block's tile reference
				--movingTilesMap(conv_integer(instruction(3 downto 0))) <= instruction(9 downto 4);
			when "100" => -- set background block
				--backgroundMap(conv_integer(instruction(6 downto 0)))(conv_integer(instruction(12 downto 7))) <= instruction(18 downto 13);
			when others =>
		end case;
	end process;

end Behavioral;


