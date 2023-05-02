import React from 'react';

export default function Header({ city }) {
  return (
    <header className='header w-full h-1/5 bg-green-400'>
      <ul className='list py-3 px-3'>
        <li className='list-item w-fit rounded-lg p-3  hover:cursor-pointer text-white hover:bg-green-500 hover:transition-all '>
          {city}
        </li>
      </ul>
    </header>
  );
}
