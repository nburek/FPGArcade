----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:41:14 03/28/2011 
-- Design Name: 
-- Module Name:    Video_Ram - Behavioral 
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

entity Video_Ram is
    Port ( clk50Mhz : in STD_LOGIC;
			  instruction : in  STD_LOGIC_VECTOR(31 downto 0);
			  instructionClk : in STD_LOGIC;
           positionX : in  STD_LOGIC_VECTOR(9 downto 0);
           positionY : in  STD_LOGIC_VECTOR(8 downto 0);
           currentPixel : out  STD_LOGIC_VECTOR(7 downto 0));
end Video_Ram;

architecture Behavioral of Video_Ram is

component tile_graphics_bram
	port (
	clka: in std_logic;
	wea: in std_logic_vector(0 downto 0);
	addra: in std_logic_vector(11 downto 0);
	dina: in std_logic_vector(7 downto 0);
	clkb: in std_logic;
	addrb: in std_logic_vector(11 downto 0);
	doutb: out std_logic_vector(7 downto 0));
end component;

-- Synplicity black box declaration
attribute syn_black_box : boolean;
attribute syn_black_box of tile_graphics_bram: component is true;

component block_graphics_bram
	port (
	clka: in std_logic;
	wea: in std_logic_vector(0 downto 0);
	addra: in std_logic_vector(12 downto 0);
	dina: in std_logic_vector(5 downto 0);
	clkb: in std_logic;
	addrb: in std_logic_vector(12 downto 0);
	doutb: out std_logic_vector(5 downto 0));
end component;

-- Synplicity black box declaration
attribute syn_black_box of block_graphics_bram: component is true;


signal tileSetWrAddr : std_logic_vector(11 downto 0);
signal tileSetReAddr : std_logic_vector(11 downto 0);
signal tileSetOutputData : std_logic_vector(7 downto 0);
signal tileSetInputData : std_logic_vector(7 downto 0);
signal WEA : std_logic_vector(0 downto 0) := "1";

signal blockSetWrAddr : std_logic_vector(12 downto 0):= "0000000000000";
signal blockSetReAddr : std_logic_vector(12 downto 0):= "0000000000000";
signal blockSetOutputData : std_logic_vector(5 downto 0):= "000000";
signal blockSetInputData : std_logic_vector(5 downto 0):= "000000";

type transparencySet is array(1023 downto 0) of STD_LOGIC;
signal movingBlocksTransparencyMap : transparencySet := (others => '0');
type moving_blocks_x is array (15 downto 0) of STD_LOGIC_VECTOR(9 downto 0); -- the x coordinates of all the moving tile
type moving_blocks_y is array (15 downto 0) of STD_LOGIC_VECTOR(8 downto 0); -- the y coordinates of all the moving tile
signal movingBlocksX : moving_blocks_x := (others => "1010000000");
signal movingBlocksY : moving_blocks_y := (others => "000000000");

signal tileX : STD_LOGIC_VECTOR(2 downto 0);
signal tileY : STD_LOGIC_VECTOR(2 downto 0);

begin
			
tileSetBRAM : tile_graphics_bram
		port map (
			clka => clk50Mhz,
			wea => WEA,
			addra => tileSetWrAddr,
			dina => tileSetInputData,
			clkb => clk50Mhz,
			addrb => tileSetReAddr,
			doutb => currentPixel);

blockSetBRAM : block_graphics_bram
		port map (
			clka => clk50Mhz,
			wea => WEA,
			addra => blockSetWrAddr,
			dina => blockSetInputData,
			clkb => clk50Mhz,
			addrb => blockSetReAddr,
			doutb => blockSetOutputData);
			
process (positionX, positionY)
	variable tempX : integer;
	variable tempY : integer;
begin
	blockSetReAddr <= conv_std_logic_vector(conv_integer(positionY(8 downto 3))*80 + conv_integer(positionX(9 downto 3)),13);
	tileX <= positionX(2 downto 0);
	tileY <= positionY(2 downto 0);
	
	for i in 15 downto 0 loop
		tempX := conv_integer(movingBlocksX(i)(9 downto 0));
		tempY := conv_integer(movingBlocksY(i)(8 downto 0));
		-- check if it's inside this moving block
		if (positionX>=tempX and positionX<=(tempX+7) and
				positionY>=tempY and positionY<=(tempY+7)) then
			
			-- check if it's on a transparent bit
			if (movingBlocksTransparencyMap(conv_integer(conv_std_logic_vector(i,6) & conv_std_logic_vector(conv_integer(positionY-tempY),3) & conv_std_logic_vector(conv_integer(positionX-tempX),3))) = '0') then
				blockSetReAddr <= conv_std_logic_vector(4800 + i,13);
				tileX <= conv_std_logic_vector(conv_integer(positionX-tempX),3);
				tileY <= conv_std_logic_vector(conv_integer(positionY-tempY),3);
			end if; -- end if pixel is not set to transparent
		end if; -- end if inside moving block
	end loop;
		
end process;

process (blockSetOutputData)
begin
	tileSetReAddr <= blockSetOutputData & tileX(2 downto 0) & tileY(2 downto 0);
end process;


process (instructionClk)
begin
		if (instructionClk'EVENT AND instructionClk = '1') then
			if instruction(31 downto 29) = "000" then -- set pixel in tile
				tileSetWrAddr <= instruction(19 downto 8);
				tileSetInputData <= instruction(7 downto 0);
			elsif instruction(31 downto 29) = "001" then -- set row transparency on moveable block
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "000")) <= instruction(7);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "001")) <= instruction(8);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "010")) <= instruction(9);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "011")) <= instruction(10);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "100")) <= instruction(11);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "101")) <= instruction(12);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "110")) <= instruction(13);
				movingBlocksTransparencyMap(conv_integer(instruction(6 downto 0) & "111")) <= instruction(14);
			elsif instruction(31 downto 29) = "010" then -- change location of moveable block
				movingBlocksX(conv_integer(instruction(22 downto 19))) <= instruction(9 downto 0);
				movingBlocksY(conv_integer(instruction(22 downto 19))) <= instruction(18 downto 10);
			elsif instruction(31 downto 29) = "011" then -- set moveable block's tile reference
				blockSetWrAddr <= conv_std_logic_vector(4800 + conv_integer(instruction(3 downto 0)),13);
				blockSetInputData <= instruction(9 downto 4);
			elsif instruction(31 downto 29) = "100" then -- set background block
				blockSetWrAddr <= conv_std_logic_vector(conv_integer(instruction(12 downto 7))*80 + conv_integer(instruction(6 downto 0)),13);
				blockSetInputData <= instruction(18 downto 13);
			end if;
		end if;

end process;
			
end Behavioral;

