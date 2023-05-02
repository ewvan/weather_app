import React from 'react';
import WeatherBlock from './WeatherBlock';

export default function Main({ data, days }) {
  return (
    <main className='weather-app rounded-lg max-w-xxlg h-100 m-3 bg-green-400 text-white p-3'>
      <h1 className='text-3xl p-4'>Weather app</h1>
      <div className='application bg-aqua-400 '>
        {data.map((day, index) => {
          if (index + 1 <= days) {
            return (
              <WeatherBlock
                key={Math.floor(Math.random() * 1000)}
                days={day.day}
                afternoon={day.afternoon}
                evening={day.evening}
                morning={day.morning}
                night={day.night}
                whole_day={day.whole_day}
              />
            );
          }
        })}
      </div>
    </main>
  );
}
